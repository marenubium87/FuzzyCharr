from discord.ext import commands
import re
import os
import asyncio

trustedUsersList = os.getenv("TRUSTED_USERS_LIST").split(", ")
TRUSTED_USERS = {os.getenv(name.upper()): name for name in trustedUsersList}
MSG_DELAY = int(os.getenv("MSG_DELAY"))
CMD_PHRASE = os.getenv("CMD_PHRASE")

class mainCmds(commands.Cog):
    def __init__(self, bot):
        self.bot = bot

    @commands.Cog.listener()
    async def on_ready(self):
        print('Logged in as ' + self.bot.user.name)
        print(self.bot.user.id)
        print('Newton is online.')

    @commands.Cog.listener()
    async def on_message(self, message):
        response = ""
        if message.author == self.bot.user.name:
            return
        elif message.content[:len(CMD_PHRASE)] == CMD_PHRASE:
            return
        elif str(message.author.id) not in TRUSTED_USERS:
            if "hi, newton" in message.content.lower():
                response = ("Hi, " + message.author.name + "\n"
                            "Your user ID is " + str(message.author.id))
        elif str(message.author.id) in TRUSTED_USERS:
            if "hi, newton" in message.content.lower():
                response = ("Hi, " + TRUSTED_USERS[str(message.author.id)] + "!")

            elif "bye, newton" in message.content.lower():
                response = ("Bye, " + TRUSTED_USERS[str(message.author.id)] + "!")
            elif re.search(r"am i \S+\?", message.content.lower()) is not None:
                wList = str(re.search(r"am i \S+\?", message.content.lower()).group(0)).split()
                word = wList[len(wList)-1]
                name = word[:-1]
                if name in (user.lower() for user in trustedUsersList):
                    if TRUSTED_USERS[str(message.author.id)].lower() != name:
                        response = "No."
                    else:
                        response = "Yes."
                else:
                    response = "I do not know of this individual."
            else:
                response = ""
        await asyncio.sleep(MSG_DELAY)
        if response != "":
            await message.channel.send(response)

def setup(bot):
    bot.add_cog(mainCmds(bot))