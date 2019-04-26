#!/usr/bin/env python
# -*- coding:utf-8 -*-
import paramiko

HOST = "172.20.10.5"
USER = "root"
PWD = "pwd123"
PORT = 22

# 连接linux server
def connect_linux(HOST, PORT, USER, PWD):
    """
      测试链接Linux函数，Client = paramiko.SSHClient()
    """
    Client = paramiko.SSHClient()
    
    try:
        Client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        Client.connect(HOST, PORT, USER, PWD, timeout=10)
    except Exception as e:
        print(e)
    return Client

# 上传 文件至linux server
def put_linux(Client, windows_file, linux_file):
    try:
        sftp = Client.open_sftp()
        sftp.put(windows_file, linux_file)
        sftp.close()
        
        return True
    except Exception as e:
        print(e)

# 获取 linux server 文件
def get_linux(Client, linux_file, windows_file):
    try:
        sftp = Client.open_sftp()
        sftp.get(linux_file, windows_file)
        sftp.close()

        return True
    except Exception as e:
        print(e)


def main_put():
    Client = connect_linux(HOST, PORT, USER, PWD)
    windows_path = input("请您输入windows文件路径：").strip()
    linux_path = input("请您输入Linux文件路径：").strip()
    
    if put_linux (Client, windows_path, linux_path):
        print(f"恭喜您，上传{windows_path}文件成功，请在Linux系统中的{linux_path}目录下查看...")
    else:
        print("对不起，上传文件失败，请您重试....")
        return False


def main_get():
    Client = connect_linux(HOST, PORT, USER, PWD)
    linux_path = input("请您输入Linux文件路径：").strip()
    windows_path = input("请您输入windows文件路径：").strip()
    
    if get_linux(Client, linux_path, windows_path):
        print(f"恭喜您，下载{linux_path}文件成功，请在Windows系统中的{windows_path}目录下查看...")
    else:
        print("对不起，下载文件失败，请您重试....")
        return False


def main():
    menu = {
        "1" : "上传文件",
        "2" : "下载文件"
    }
    
    for k, v in menu.items():
        print(f"{k}、{v}")
    
    your = input("请您输入:").strip()
    
    if your == "1":
        main_put()
    elif your == "2":
        main_get()
    
if __name__ == "__main__":
    main()
