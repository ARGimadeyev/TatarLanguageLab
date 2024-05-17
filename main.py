from config import *


import logging, asyncio
from aiogram import Bot, Dispatcher, types
from aiogram.filters.command import Command
# from aiogram.types import InlineKeyboardButton, InlineKeyboardMarkup, FSInputFile
# from aiogram.utils.keyboard import InlineKeyboardBuilder, ReplyKeyboardBuilder
# from aiogram import F


logging.basicConfig(level=logging.INFO)
bot = Bot(token=BOT_TOKEN)
dp = Dispatcher()



@dp.message(Command("start"))
async def start(message: types.Message):
    await message.answer("Приветствуем вас снова ")


async def main():
    await dp.start_polling(bot)


if __name__ == "__main__":
    asyncio.run(main())