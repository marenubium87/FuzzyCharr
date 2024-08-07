import os
#loads environmental variables
from dotenv import load_dotenv
#logging module
import logging
from logging.config import dictConfig
import discord

DISCORD_API_KEY = os.getenv("DISCORD_TOKEN")

GUILD_ID = discord.Object(id=int(os.getenv('GUILD_ID')))

LOGGING_CONFIG = {
    'version': '0.1',
    'disabled_existing_loggers': False,
    'formatters': {
        'verbose': {
            'format': '%(levelname)-10s - %(asctime)s -%(module)-15s : %(message)s'
        },
        'standard': {
            'format': '%(levelname)-10s : %(message)s'
        }
    },
    'handlers': {
        'console': {
            'level': 'DEBUG',
            'class': 'logging.StreamHandler',
            'formatter': 'standard'
        },
        'console2': {
            'level': 'WARNING',
            'class': 'logging.StreamHandler',
            'formatter': 'standard'
        },
        'file': {
            'level': 'INFO',
            'class': 'logging.FileHandler',
            'filename': 'info.log',
            'filemode': 'w',
            'formatter': 'verbose'
        }
    },
    'loggers': {
        'bot': {
            'handlers': ['console', 'file'],
            'level': 'INFO',
            'propagate': False
        },
        'discord': {
            'handlers': ['console2', 'file'],
            'level': 'INFO',
            'propagate': False
        }
    }

}