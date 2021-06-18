from discord.ext import commands
import re
import os
import asyncio
import math
from datetime import date

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
            await asyncio.sleep(MSG_DELAY)
            await ctx.send(f'Please give a reason:')

            #Makes sure that response will only be registered if following
            #conditions are met:
            #(specifically, if it's me)
            def check(msg):
                return msg.author == ctx.author
            
            reason = await self.bot.wait_for('message', check=check)
            await asyncio.sleep(MSG_DELAY)
            await ctx.send("So noted.")

            #opens leveling documents for writing
            #appends to leveling notes
            f1 = open(r"data/leveling.txt", mode = 'r')
            f2 = open(r"data/levelingNotes.txt", mode = 'a')

            #0th entry is level, 1st entry is xp
            levelData = f1.read().split(' ')
            f1.close()

            #append to log file
            f2.write(f'{date.today().isoformat()}  Assigned {xp} XP for ' +
            f'\'{reason.content}\'\n')
            f2.close()

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
            xpFile.close()
            await asyncio.sleep(MSG_DELAY)
            await ctx.send(response)

   
def setup(bot):
    bot.add_cog(xpOps(bot))
