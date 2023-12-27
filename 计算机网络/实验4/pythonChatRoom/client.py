from socket import *
from multiprocessing import Process
import sys

# 服务器地址
ADDR = ('127.0.0.1', 8888)

# 处理登录
def login(socketed):
    while True:
        # 进入聊天室
        name = input('Please input your nickname：')

        # 发送姓名给服务端
        msg = 'LOGIN ' + name
        # encode()函数将目标字符串编写为目标二进制数据bytes类型，编码过程
        socketed.sendto(msg.encode(), ADDR)
        # 接收服务端结果反馈
        data, address = socketed.recvfrom(1024)
        # decode()函数将编码后的字符串转换为原始字符串，解码过程
        if data.decode() == 'YES':
            print('Welcome %s ,input<quit> to quit the chat!' % (name,))
            return name
        else:
            print('%s has exited' % (name,))

# 子进程，循环接收消息
def chat(socketed, name):
    while True:
        data, address = socketed.recvfrom(1024 * 10)
        # 美化打印内容
        msg = "\n" + data.decode() + "\n[%s]: " % name
        print(msg, end="")  # end="" 不换行

# 父进程，循环发送消息
def receive(socketed, name):
    while True:
        # try 处理异常退出
        try:
            news = input('[%s]：' % (name,))
        except KeyboardInterrupt:
            news = 'EXIT'

        if news == 'quit':
            msg = 'EXIT ' + name
            socketed.sendto(msg.encode(), ADDR)
            sys.exit('%s has left the chat!' % (name,))

        msg = 'CHAT %s %s' % (name, news)
        # 发送编码结果到指定位置
        socketed.sendto(msg.encode(), ADDR)

# 程序启动函数
def main():
    socketed = socket(AF_INET, SOCK_DGRAM)
    name = login(socketed)  # 进入聊天室

    # 创建子进程　用于接收消息
    process = Process(target=chat, args=(socketed, name))
    process.daemon = True  # 父进程退出子进程也退出
    process.start()

    # 父进程发送消息
    receive(socketed, name)
    socketed.close()
    process.join()

if __name__ == '__main__':
    main()
