'''
Created on Sep 1, 2016

@author: Drakonnas
'''
 
HOST = "irc.twitch.tv"                          # Twitch irc host
PORT = 6667                                     # IRC port
CHAN = "#drakonnas"                               # CHAN = the channel to connect to
NICK = "aphelionbot"                            # NICK = Twitch username
PASS = "oauth:zhdtugz4k6v1chm1khodrv6b72hz9f"   # authkey for the NICK
RATE = (100/30)  # 100 per 30 seconds = Mod   ||||   20 per 30 seconds = User
EXIT = "Shutting down, goodbye!"
PATT = [
    r"I hate you Drake",
    r"I hate Drakonnas",
    r"Drake is a bad mod",
    r"Drakonnas is a bad mod"
    ]