from socket import *
from multiprocessing import Process

# 服务器地址
HOST='0.0.0.0'
PORT= 8888
ADDR = (HOST,PORT)
# 用字典储存用户
user = {}  # 储存用户信息　{name:address}格式

# 处理进入聊天室
def login(socketed, name, address):
    # 判断姓名是否已存在或者姓名为admin
    if name in user or 'admin' in name:
        socketed.sendto('NO'.encode(), address)
    else:
        socketed.sendto('YES'.encode(), address)
        # 循环通知其他人
        msg = '%s had joined the chat!' % name
        for other in user:
            socketed.sendto(msg.encode(), user[other])
        user[name] = address  # 增加该用户

# 处理聊天
def chat(socketed, name,content):
    msg = "[%s]: %s" % (name, content)
    for other in user:
        if other == name:
            continue  # 除去自己
        socketed.sendto(msg.encode(), user[other])

# 处理退出
def exits(socketed, name):
    del user[name]  # 删除用户
    msg = '%s has left the chat!' % name
    for other in user:
        socketed.sendto(msg.encode(), user[other])

# 处理客户端请求
def request(socketed):
    # 循环接收各种客户端请求
    while True:
        # 接收所有客户端请求
        data, address = socketed.recvfrom(1024)
        # 对数据结构进行简单解析
        tmp = data.decode().split(' ',2)

        if tmp[0] == 'LOGIN':
            # tmp---> ['LOGIN','name']
            # 进入函数
            login(socketed, tmp[1], address)
        elif tmp[0] == 'CHAT':
            # tmp---> ['LOGIN','name','news']
            # 　聊天函数
            chat(socketed, tmp[1],tmp[2])
        elif tmp[0] == 'EXIT':
            # 退出函数
            exits(socketed, tmp[1])

# 程序启动函数
def main():
    # UDP套接字
    socketed = socket(AF_INET, SOCK_DGRAM)
    socketed.bind(ADDR)
    # 创建子进程
    process=Process(target=request,args=(socketed,))
    process.daemon=True # 父进程退出子进程也退出
    process.start()
    while True:
        # 发送管理员消息
        content = input("message from admin：")
        # 服务端退出
        if content == "EXIT":
            break
        msg = "CHAT message from admin： "+content
        # 从父进程发送给子进程
        socketed.sendto(msg.encode(),ADDR)

if __name__ == '__main__':
    main()

