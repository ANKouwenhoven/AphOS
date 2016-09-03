'''
Created on Sep 1, 2016

@author: Drakonnas
'''

import cfg
import socket
import time
import re
import msvcrt
 
 
def chat(sock, msg):
    sock.send('PRIVMSG {} :{}\r\n'.format(cfg.CHAN, msg).encode(encoding='utf_8', errors='strict'))
 
 
def ban(sock, user):
    sock.send('PRIVMSG {} :.ban {}\r\n'.format(cfg.CHAN, user).encode(encoding='utf_8', errors='strict'))
 
 
def timeout(sock, user, secs):
    sock.send('PRIVMSG {} :.timeout {} {}\r\n'.format(cfg.CHAN, user, secs).encode(encoding='utf_8', errors='strict'))
    
def keyboard():
    x = msvcrt.kbhit()
    if x:
        ret = ord(msvcrt.getch())
    else:
        ret = 0
    return ret 
 
CHAT_MSG = re.compile(r"^:\w+!\w+@\w+\.tmi\.twitch\.tv PRIVMSG #\w+ :")
CHANNEL_OWNER = cfg.CHAN.lstrip('#')
 
# network functions
s = socket.socket()

s.connect((cfg.HOST, cfg.PORT))
s.send("PASS {}\r\n".format(cfg.PASS).encode("utf-8"))
s.send("NICK {}\r\n".format(cfg.NICK).encode("utf-8"))
s.send("JOIN {}\r\n".format(cfg.CHAN).encode("utf-8"))

chat(s, "Aphelion active.")
print("Announced my arrival.") 
 
while True:
    
    if msvcrt.kbhit():
        ch = msvcrt.getch()
        if ch == b's':
            chat(s, cfg.EXIT)
            print("Exiting.")
            exit()
    
    response = s.recv(1024).decode("utf-8")
    if response == "PING :tmi.twitch.tv\r\n":
        s.send("PONG :tmi.twitch.tv\r\n".encode("utf-8"))
        print("Ponged the Ping.")
    else:        
        username = re.search(r"\w+", response).group(0)  # return the entire match
        message = CHAT_MSG.sub("", response)
        print(username + ": " + message)
        for pattern in cfg.PATT:
            if re.match(pattern, message):
                timeout(s, username, 1)
                chat(s, username + " has been timed out for messing with the wrong mod.")
                print("I tried to time out " + username)
                break
            
        # kill bot
        
        if (re.match("!botstop", message)):
            if (re.match(CHANNEL_OWNER, username) or re.match("drakonnas", username)):
                chat(s, cfg.EXIT)
                print("I'm being asked to shut down by " + username)
                exit()
            else:
                chat(s, "Sorry, you don't have permission to call this command.")
                print(username + " tried to shut me down!")
            
        # ~commands    
            
        if re.match("~test", message):
            chat(s, "Kappa test!")
            print("Announced a Kappatest")
            
        if re.match("~badjoke", message):
            chat(s, "I can't believe you've done this.")
            print("Replied to a bad joke")
            
        # chat triggers
            
        if (re.match("paladins", message) or re.match("Paladins", message)):
            chat(s, "Paladins DansGame")
            print("Insulted Paladins")
            
        if (re.match("Tilly o/", message) or re.match("tilly o/", message)):
            chat(s, "Tilly <3")
            print("Found the Tilly")
            
        if 'now has 0 AzulW' in message:
            chat(s, "RIP!")
            print("Somebody lost all his AzulW!")
            
        time.sleep(1 / cfg.RATE)