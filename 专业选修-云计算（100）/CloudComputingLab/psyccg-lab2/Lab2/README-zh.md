#Lab2：您自己的HTTP服务器
*部分材料来自加州大学伯克利分校CS162 2019的作业3。**感谢CS162！*
输入您从我们的实验室git repo克隆的文件夹，并提取最新的提交-使用“git pull”。
您可以在“lab2/README.md”中找到此lab2的说明
lab2的所有材料都在文件夹“lab2/”中。
1.概述
使用从我们班学到的网络编程知识，自己从头开始实现基于HTTP/1.1的HTTP服务器。
此外，尝试使用从课堂上学到的高并发编程技能来保证web服务器的性能。
**我们的目标：**
*练习基本的网络编程技巧，如使用socket API，解析数据包；
*熟悉健壮且高性能的并发编程。
2.后退
**请先查看[background.md]（./background.md），了解有关“HTTP”、“HTTP消息”、“HTTP代理”、“JSON”和“curl”的一些基础知识**
3.您的实验室任务
##实现您自己的HTTP服务器
在这个实验室里，我们不会提供任何基本的代码。您应该从头开始实现一个基于HTTP/1.1的HTTP服务器，它满足以下要求：
**HTTP服务器大纲**
从网络的角度来看，您的HTTP服务器应该实现以下内容：
1.创建一个监听套接字，并将其绑定到一个端口；
1.等待客户端连接到端口；
1.接受客户端并获得新的连接套接字；
1.读取并解析HTTP请求；
1.开始提供服务（*有些是可选的*）：
*处理HTTP GET/POST请求和返回响应。
*将请求代理到另一个HTTP服务器。
服务器将处于非代理模式或代理模式（我们在背景部分“2.3”中介绍了代理）。它不会同时做这两件事。
为了更好的测试和评分，我们对您提交的作品提出了**一些功能要求**。
**注意**：实验室2是实验室4的预备实验室。如果您计划完成实验室4，请完成实验室2的高级版本**。

###3.1处理HTTP请求并发送HTTP响应
在这个实验室中，**您只需要在HTTP服务器中实现GET方法和POST方法**。
对于任何其他方法，您的服务器应发送一个带有501状态代码的响应（请参阅“2.2”）。
也就是说，如果您的HTTP服务器接收到HTTP请求，但请求方法既不是GET也不是POST，则HTTP服务器只需要返回一条501 Not Implemented错误消息（一条响应消息，其响应行的状态代码为501，请参阅“2.2”）。
请参阅第[3.7]节中的示例（#37访问您的http服务器）。

####3.1.1处理HTTP GET请求
HTTP服务器应该能够处理特定资源的HTTP GET请求，例如web服务数据和静态文件。
对于GET请求，服务器需要检查请求的路径是否对应于web服务或已存在的静态文件。
您需要做的事情：
**基本版本**：
*搜索服务：使用特定的url从服务器获取一些数据，这些数据不是来自存储在文件系统上的文件。
*url没有查询字符串，例如`http://localhost:8080/api/check`;
*用纯文本内容发送响应。
*静态文件访问：使用特定的url访问存储在文件系统上的文本文件。
*客户端仅请求`*.html`；
*客户端可以请求子目录中的文件，例如`http://localhost:8080/test/index.html`;
*用html文件的全部内容发送响应。
*如果路径无效或静态文件不存在
*发送包含“404未找到”页面完整内容的响应。
**高级版本**：
*搜索服务：使用特定的url从服务器获取一些数据，这些数据不是来自存储在文件系统上的文件。
*url可能有查询字符串，例如`http://localhost:8080/search?id=1&name=foo`;
*查询字符串包含一些键值对。键为`id`和`name`；
*如果查询字符串有效，则发送包含json类型内容的响应。
*或者，如果无效，则发送json类型内容的响应，包括错误消息；
*静态文件访问：使用特定的url访问存储在文件系统上的文本文件。
*客户端可以请求`*.html`、`*.js`、`'.css`、`*.json`和其他纯文本文件；
*客户端可以请求子目录中的文件，例如`http://localhost:8080/test/index.html`;
*发送具有正确“内容类型”和文件完整内容的响应。
*如果路径无效或静态文件不存在
*发送包含“404未找到”页面完整内容的响应。
*您不需要实现传输base64编码的二进制文件，例如像*.png`.*这样的图像文件

####3.1.2处理HTTP POST请求
HTTP服务器应该能够处理HTTP POST请求。
对于POST请求，服务器需要检查请求的路径是否对应于web服务。
>对于特殊字符，如“%”，您可能需要在谷歌上搜索编码**的百分比。
您需要做的事情：
**基本版本**：
*上传服务：使用特定的url将一些数据上传到服务器
*内容类型为`application/x-www-form-urlencoded`；
*有效载荷包含键值对，键为`id`和`name`；
*如果有效载荷有效，则发送带有“200 OK”、“Content Type:text/plain”&data；
*或者，如果有效载荷无效，则发送带有“404未找到”、“内容类型：text/plain”的发送响应的响应&错误消息；
*如果路径无效
*发送包含“404未找到”页面完整内容的响应。
**高级版本**：
*上传服务：使用特定的url从服务器上传一些数据，这些数据不是来自存储在文件系统上的文件。
*内容类型为`application/x-www-form-urlencoded`，`application/json`；
*有效载荷包含键值对，键为`id`和`name`；
*如果有效负载有效，则发送带有`200 OK `、`Content Type:application/json`&data的响应；
*或者，如果有效载荷无效，则发送带有“404 Not Found”、“Content Type:application/json”的发送响应的响应&错误消息；
*如果路径无效
*发送包含“404未找到”页面完整内容的响应。
如果您不熟悉“application/x-www-form-urlencoded”，请检查[MDN docs](https://developer.mozilla.org/en-US/docs/Learn/Forms/Sending_and_retrieving_form_data).

####3.1.3其他要求
对于其他请求方法（如DELETE、PUT等），只需返回501 Not Implemented页面即可。

###3.2实现代理服务器（高级版本可选）
使您的服务器能够将HTTP请求代理到另一个HTTP服务器，并将响应转发到客户端。
1.您应该使用“--proxy”命令行参数的值，该参数包含上游HTTP服务器的地址和端口号。
2.代理服务器应该等待两个套接字上的新数据（HTTP客户端文件描述符和上游HTTP服务器文件描述符）。当数据到达时，您应该立即将其读取到缓冲区，然后将其写入另一个套接字。您基本上是在维护HTTP客户端和上游HTTP服务器之间的双向通信。请注意，您的代理必须支持多个请求/响应。
3.如果其中一个套接字关闭，则通信无法继续，因此应关闭另一个套接字并退出子进程。
提示：1）这比写入文件或从stdin读取更棘手，因为您不知道双向流的哪一侧将首先写入数据，也不知道它们是否会在收到响应后写入更多数据。2） 您应该再次为此任务使用线程。例如，考虑使用两个线程来促进双向通信，一个从A到B，另一个从B到A。
>大多数网站现在使用HTTPS，并将检查您的HTTP头行，您的代理服务器可能不适合任何web服务器。
>
>实现HTTP以外的协议不是我们的任务。
>
>它们通常涉及加密算法，并且很难直接使用套接字api来实现。
>
>但是，如果您对HTTPS等协议感兴趣，可以尝试使用其他库，例如openssl。

###3.3使用多线程增加并发
您的HTTP服务器应该使用多个线程来处理尽可能多的并发客户端请求。您至少有以下三个选项来构建多线程服务器：
-**按需线程**。您可以在新客户端进入时创建一个新线程，并使用该线程来处理所有客户端的任务，包括解析HTTP请求、获取页面文件和发送响应。线程可以在客户端完成后销毁，例如，通过TCP“recv（）”进行检测。然而，在HTTP层中检测客户端完成可能并不容易。
-**一个常开线程池**。您可以在HTTP服务器程序中使用固定大小的线程池来同时处理多个客户端请求。如果没有任务，则这些线程处于等待状态。如果有新的客户端进入，请分配一个线程来处理客户端的请求并向其发送响应。如果分配的线程很忙，您可以使用工作队列来缓冲请求，并让线程稍后处理它。
-**组合**。将以上两种样式组合在一起。例如，您可以使用线程池来接收请求和发送响应，并使用按需线程来获取大型页面文件。
可以从上面三个中任意选择一个，或者使用其他你认为很酷的多线程架构。

###3.4支持HTTP流水线
在基本版本中，每个TCP连接同时**只有一个请求。客户端等待响应，当它得到响应时，可能会将TCP连接重新用于新请求（或使用新的TCP连接）。这也是普通HTTP服务器所支持的。
在高级版本中，**可以在一个TCP连接上同时触发多个http请求**。这也被称为HTTP流水线，它受到许多真实浏览器和服务器（如Chrome）的支持。请注意，来自同一TCP连接的HTTP请求应该以相同的顺序响应。因此，在使用复杂的多线程样式时要注意顺序问题。

###3.5指定参数
您的程序应该启用长选项来接受参数，并在启动过程中指定这些参数。
他们是：
|参数|描述|
| --- | --- |
|-i，-ip\<ip\>|指定服务器ip地址|
|-p，--port\<port\>|选择HTTP服务器侦听传入连接的端口|
|--proxy\<proxy\>|选择一个“上游”HTTP服务器进行代理|
|-t，--threads\<threads\>|如果使用多线程，则为线程数|
“--proxy”可以在“：//”之前有一个schema，在冒号之后有一个端口号（例如`http://www.example.com:80`). 如果未指定端口号，则端口80是HTTP的默认端口号。
如果你不知道长选项，你可以阅读(https://www.gnu.org/software/libc/manual/html_node/Argument-Syntax.html#Argument-语法）。您可能需要使用一些函数，如“getopt_long（）”、“getopt_long_only（）”和“getopt（）”等。请使用“man”命令检查这些函数的使用情况。

###3.6运行HTTP服务器
**对于高级版本**：
您的程序应该能够在终端启动。如果您的程序名为*http server*，只需键入：
在非代理模式下：
`./http服务器--ip 127.0.0.1--端口8888--线程8`
这意味着您的HTTP服务器的IP地址为127.0.0.1，服务端口为8888。--number线程表示线程池中有8个线程用于同时处理多个客户端请求。
在代理模式下：
`./http服务器--ip 127.0.0.1--端口8888--线程8--代理http://www.example.com:80`
这意味着这是一个HTTP代理服务器。此代理的IP地址为127.0.0.1，服务端口为8888。代理有一个包含8个线程的线程池。--proxy表示“上游”HTTP服务器`http://www.example.com:80`. 因此，如果您向该代理发送请求消息（即“127.0.0.1:8888”），它将把该请求消息转发到“上游”HTTP服务器（即`http://www.example.com:80`)并将响应消息转发给客户端。
>如果你想从其他主机访问这台服务器，也许你应该打开端口对应的防火墙，并将ip绑定到0.0.0.0。
当您运行上面的命令时，您的HTTP服务器应该会正确运行。

###3.7访问您的HTTP服务器
我们假设服务器绑定的ip是“127.0.0.1”，端口是“8080”。如果使用了代理功能，则远程服务器为“www.example.com”。
为了更高效的测试和评分，我们需要您实现下面描述的一些接口，并确保响应的内容与我们的期望一致。
**这就是我们提供一些标准静态文件的原因。你可以在`中签入那些文件/静止的数据
请确保您的服务器支持访问它们，并且**不要修改它们的内容或相对路径**。

####3.7.1使用GET方法
**1） 访问静态文件**
对于**基本**版本：
|路径|本地fs中的文件|状态代码|内容类型|
| --- | --- | --- | --- |
|/，/index.html|/`{static-dir}`/index.html|200|text.html|
|/404.html |/`{static-dir}`/404.html | 404|text.html|
|/501.html |/`{static-dir}`/501.html | 501|text.html|
|任何其他错误路径|/`{static-dir}`/404.html|404|text.html|
例如。：
壳
user@linux：~/http服务器$curl-i-X GEThttp://localhost:8080/index.html
HTTP://1.1 200 OK
内容类型：text/html
内容长度：210
<!DOCTYPE html>
<html lang=“en”>
头
<meta charset=“UTF-8”>
<link rel=“stylesheet”href=“/styles.css”/>
＜title＞Http服务器</title＞
头
</body>
<h1>index.html</h1>
</body>
</html>
```
对于**高级**版本：
|路径|本地fs中的文件|状态代码|内容类型|
| --- | --- | --- | --- |
|/，/index.html|/`{static-dir}`/index.html|200|text.html|
|/404.html |/`{static-dir}`/404.html | 404|text.html|
|/501.html |/`{static-dir}`/501.html | 501|text.html|
|[/\*]/\*.html|/`｛static dir｝`[/\*]/\*.html|200|text.html|
|[/\**]/\*.js|/`｛static dir｝`[/\**]/\*.js|200|text/javascript|
|[/\*]/\*.css |/`｛static dir｝`[/\*]/\*.css |200|text/css|
|[/\*]/\*.json|/`｛static dir｝`[/\*]/\*.json|200|application/json|
|任何其他错误路径|/`{static-dir}`/404.html|404|text.html|
```
user@linux：~/http服务器$curl-i-X GEThttp://localhost:8080/data.json
HTTP://1.1 200 OK
内容类型：application/json
内容长度：93
[｛“id”：1，“name”：“Foo”｝，｛“id2，”name“：“Bar”｝
```
>对于标准化测试，在一行中输出JSON数据，不需要不必要的空格。
**2） 访问web服务以获取数据**
对于**基本**版本：
|路径|获取数据|状态代码|内容类型|
| --- | --- | --- | --- |
|/api/check|`data.txt`中的字符串|200|text/plain|
|任何其他错误路径|/｛static files｝/404.html |404|text.html|
例如。：
壳
user@linux：~/http服务器$curl-i-X GEThttp://localhost:8080/api/check
HTTP://1.1 200 OK
内容类型：text/plain
内容长度：13
id=1&name=Foo
```
对于**高级**版本：
|路径|获取数据|状态代码|内容类型|
| --- | --- | --- | --- |
|/api/list|`data.json`中的所有对象|200|application/json|
|/api/search？[id=`value1`&name=`value2`]|在`/data/data.json`|200|application/json中匹配<br/>`*.id==value1&&&*.name==value2`<br/>的所有对象|
|/api/search？[id=`value1`&name=`value2`]|如果没有对象匹配，则返回`/data/not_fund.json`|404|application/json中的所有对象<br/>|
|任何其他错误路径|/｛static files｝/404.html |404|text.html|
>查询字符串格式为正则表达式：`id=[0-9]+&name=[a-zA-Z0-9]+`。
>如果您不想解析json文件，您可以将数据存储在内存中，而不是每次都读取文件。
例如。：
壳
user@linux：~http://http服务器$curl-i-G-d'id=1&name=Foo'\
>-X获取http://localhost:8080/api/search
HTTP://1.1 200 OK
内容类型：application/json
内容长度：23
[｛“id”：1，“name”：“Foo”｝]
```
>对于标准化测试，在一行中输出JSON数据，不需要不必要的空格。

####3.7.2使用POST方法
**访问用于上载数据的web服务**
需要上载的所有数据都是两个键/值对：`id:｛value1｝`和`name:｛value2｝`。
>对于标准化测试，按“id”、“name”的顺序输出。
您的服务器应该检查数据。在默认情况下，服务器应该回显来自客户端的数据。
如果数据格式错误，例如“id=1&name”、“id=1”或“id=1&foo=a”，则发送内容错误消息。
对于**基本**版本：
客户端应发送带有“内容类型：application/x-www-form-urlencoded”的请求。
>echo数据格式是一个正则表达式：`id=[0-9]+&name=[a-zA-Z0-9]+`。
处理后，发送响应：
|路径|内容|状态代码|内容类型|
| --- | --- | --- | --- |
|/api/echo|echo接收到的数据|200|application/x-www-form-urlencoded|
|/api/echo |如果数据格式错误，请在`/data/error.txt`|404|text/plain中发送字符串<br/>|
|任何其他错误路径|/｛static files｝/404.html |404|text.html|
例如。：
壳
user@linux：~/http服务器$curl-i-d'id=1&name=Foo'\
>-H“内容类型：应用程序/x-www-form-urlencoded”\
>-X个帖子http://localhost:8080/api/echo
HTTP://1.1 200 OK
内容类型：应用程序/x-www-form-urlencoded
内容长度：13
id=1&name=Foo
```
对于**高级**版本：
客户端应发送带有“内容类型”的请求：
*`application/x-www-form-urlencoded`，
*`application/json`。
处理后，发送响应：
|路径|内容|状态代码|内容类型|
| --- | --- | --- | --- |
|/api/upload|echo接收到的数据|200|application/json|
|/api/upload|如果数据格式错误，请在`/data/error.json`|404|application/json中发送字符串<br/>|
|任何其他错误路径|/｛static files｝/404.html |404|text.html|
例如。：
壳
user@linux：~/http服务器$curl-i-d'｛“id”：1，“name”：“Foo”｝'\
>-H“内容类型：application/json”\
>-X个帖子http://localhost:8080/api/upload
HTTP://1.1 200 OK
内容类型：application/json
内容长度：21
｛“id”：1，“name”：“Foo”｝
```
>对于标准化测试，在一行中输出JSON数据，不需要不必要的空格。

####3.7.3其他方法
HTTP服务器将不处理HTTP请求，GET请求和POST请求除外。
如果使用“DELETE”（或“PUT”、“HEAD”等）发送HTTP请求以删除指定的资源，则服务器应发送“/｛static dir｝/501.html”：

###3.8实施要求
版本
***基本版本**
完成**基本版本**的所有任务，如第3.1至3.7节所述，但“3.2”除外。
***高级版本**
完成**高级版本**的所有任务，如“3.1 ~ 3.7”**节所述，包括“3.2”**。

4.测试器
我们提供了一些测试工具。
你可以查看[测试人员]的回复(https://github.com/LabCloudComputing/http-server-tester).
当然，你也可以使用自己的浏览器和其他网络工具，如curl。

5.实验室提交
请将您的所有代码放在文件夹“Lab2”中，并编写一个“Makefile”，这样我们**就可以在一个命令中编译您的代码**“make”。编译后的可运行可执行二进制文件应命名为“http server”，并位于文件夹“Lab2”中。请仔细遵守以上规则，以便TA可以自动测试您的代码！！！
请按照[总体实验室说明]（../README.md）（`../README.md`）中的指导提交您的实验室计划

6.分级标准
*如果你能：
*完成基本版本的所有要求
*如果你能：
*完成高级版本的所有要求
如果你错过了一些部分，你会得到部分分数，这取决于你完成了多少。
