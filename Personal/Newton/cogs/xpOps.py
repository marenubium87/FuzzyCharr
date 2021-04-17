from discord.ext import commands
import re
import os
import asyncio
import math

trustedUsersList = os.getenv("TRUSTED_USERS_LIST").split(", ")
TRUSTED_USERS = {os.getenv(name.upper()): name for name in trustedUsersList}
MSG_DELAY = int(os.getenv("MSG_DELAY"))
CMD_PHRASE = os.getenv("CMD_PHRASE")

class xpOps(commands.Cog):
    def __init__(self, bot):
        self.bot = bot

    @commands.command()
    async def assignXP(self, ctx, xp):
        if TRUSTED_USERS.get(str(ctx.message.author.id)) == "Aerie":
            f = open(r"data/leveling.txt", mode = 'r')

            #0th entry is level, 1st entry is xp
            levelData = f.read().split(' ')
            f.close()

            #reads current level and xp, adds xp to be committed
            curLevel = int(levelData[0])
            xpOld = int(xp)
            xpNew = xpOld

            curXP = int(levelData[1]) + xpNew
            lvlXPCalc = lambda lvl: math.floor(2.4 * math.pow(lvl + 1, 1.8) + 120)
            lvlXP = lvlXPCalc(curLevel)

            while curXP >= lvlXP:
                curLevel += 1
                #subtracts the amount of xp required to reach new level
                xpNew = xpOld - (lvlXP - (curXP - xpOld))
                response = (f'Committing {lvlXP - (curXP - xpOld)} XP to ' + 
                f'reach level {curLevel}... {xpNew} xp remain.')
                
                #new level, current XP is 0 plus whatever remaining XP there is
                #update xpOld for next cycle, if applicable
                curXP = xpNew
                xpOld = xpNew
                #update leveling amount for next level
                lvlXP = lvlXPCalc(curLevel)
                await asyncio.sleep(MSG_DELAY)
                await ctx.send(response)

            #finally, after all levels have been gained
            response = (f'Committing {xpNew} XP...\n' + 
            f'Currently at level {curLevel} \n' +
            f'{curXP} of {lvlXP} XP to level {curLevel + 1}')

            xpFile = open(r"data/leveling.txt", mode = 'w')
            xpFile.write(f'{curLevel} {curXP}')
            await asyncio.sleep(MSG_DELAY)
            await ctx.send(response)

   
def setup(bot):
    bot.add_cog(xpOps(bot))
