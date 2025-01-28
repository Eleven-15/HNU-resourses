import tkinter as tk
import sys
import subprocess
#from b import average

def start_button_clicked():
    #
    var1 = 1#average

    # 在各个文本框中显示变量的值
    var1_text.delete("1.0", tk.END)
    var1_text.insert(tk.END, var1)

    # 在输出文本框中显示 Python 的输出信息
    result = subprocess.Popen(['python', 'b.py'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    output = result.communicate()
    print(output[0].decode('utf-8'))

# 创建主窗口
window = tk.Tk()

# 创建变量1的文本框
var1_label = tk.Label(window, text="average:")
var1_label.grid(row=0, column=0)
var1_text = tk.Text(window, width=20, height=1)
var1_text.grid(row=0, column=1)

# 创建开始按钮
start_button = tk.Button(window, text="开始", command=start_button_clicked)
start_button.grid(row=6, column=0, columnspan=2)

# 创建输出文本框
output_text = tk.Text(window, width=40, height=10)
output_text.grid(row=0, column=2, rowspan=7)

# 重定向输出
class StdoutRedirector:
    def __init__(self, text_widget):
        self.text_widget = text_widget

    def write(self, text):
        self.text_widget.insert(tk.END, text)
        self.text_widget.see(tk.END)

    def flush(self):
        pass

# 将标准输出重定向到文本框
output_text_redirector = StdoutRedirector(output_text)
sys.stdout = output_text_redirector

# 运行主循环
window.mainloop()