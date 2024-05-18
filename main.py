from aiogram.filters.callback_data import CallbackData

from config import *

import logging, asyncio
from aiogram import Bot, Dispatcher, types
from aiogram.filters.command import Command
from aiogram.enums.parse_mode import ParseMode
from aiogram.client.default import DefaultBotProperties
from aiogram.types import InlineKeyboardButton, InlineKeyboardMarkup, FSInputFile, CallbackQuery, InputFile, \
    InputMediaPhoto
from aiogram.utils.keyboard import InlineKeyboardBuilder, ReplyKeyboardBuilder
from aiogram import F
from typing import Optional

logging.basicConfig(level=logging.INFO)
bot = Bot(token=BOT_TOKEN, default=DefaultBotProperties(parse_mode=ParseMode.HTML))
dp = Dispatcher()


class NumbersCallbackFactory(CallbackData, prefix="plot"):
    action: str
    value: Optional[int] = None


@dp.message(Command("start"))
async def start(message: types.Message):
    keyboard = InlineKeyboardBuilder()
    keyboard.button(text="Сюжет", callback_data=NumbersCallbackFactory(action="plot", value=0))
    keyboard.add(InlineKeyboardButton(text="Песочница", callback_data="sandbox"))
    await bot.send_photo(chat_id=message.chat.id, photo=FSInputFile("plotFiles/photo-1.jpg"),
                         caption="Выберите режим игры", reply_markup=keyboard.as_markup())


def get_keyboard(id: int):
    keyboard = InlineKeyboardBuilder()
    keyboard.button(text="Назад", callback_data=NumbersCallbackFactory(action="plot_back", value=-1))
    keyboard.button(text="Дальше", callback_data=NumbersCallbackFactory(action="plot_next", value=1))
    if user_data[id] in gameIndex:
        print(user_data[id])
        keyboard.button(text=gameTitle[user_data[id]],
                        url=f"http://t.me/TatarLanguageLabBot/{gameTitle[user_data[id]]}")
    keyboard.adjust(2)
    return keyboard.as_markup()


async def update_replic(message: types.Message, id: int):
    await message.edit_media(
        InputMediaPhoto(media=plotFiles[user_data[id]], caption=plotDialogs[user_data[id]], parse_mode="html"),
        reply_markup=get_keyboard(id))


@dp.callback_query(NumbersCallbackFactory.filter())
async def plot(call: types.CallbackQuery, callback_data: NumbersCallbackFactory):
    if call.from_user.id not in user_data:
        user_data[call.from_user.id] = 0

    user_data[call.from_user.id] += callback_data.value
    if user_data[call.from_user.id] < 0:
        user_data[call.from_user.id] = 0
        await call.message.delete()
        await start(call.message)
    elif user_data[call.from_user.id] == QUANTITYPLOT:
        await call.message.delete()
        await call.message.answer("КОНЕЦ")
        user_data[call.from_user.id] = 0
    else:
        await update_replic(call.message, call.from_user.id)


@dp.callback_query(F.data == "sandbox")
async def plot(call: types.CallbackQuery):
    await call.message.delete()
    keyboard = InlineKeyboardBuilder()
    keyboard.add(InlineKeyboardButton(text="zubrilka", url="http://t.me/TatarLanguageLabBot/zubrilka"),
                 InlineKeyboardButton(text="WOW", url="https://t.me/TatarLanguageLabBot/WOW"),
                 InlineKeyboardButton(text="Wordle", url="https://t.me/TatarLanguageLabBot/Wordlex"),
                 InlineKeyboardButton(text="4", callback_data="game4"),
                 InlineKeyboardButton(text="Назад", callback_data="back")
                 )
    keyboard.adjust(4)
    await call.message.answer("Вы долго брели по лесу и поняли, что заблудились. Вокруг вас лишь высоченные сосны и шелестящая трава. Вы поняли, что впереди вас ждут незабываемые приключения и новые знакомства, а пока можно прилечь и подучить татарский язык.", reply_markup=keyboard.as_markup())


@dp.callback_query(F.data == "back")
async def plot(call: types.CallbackQuery):
    await call.message.delete()
    await start(call.message)


async def main():
    await dp.start_polling(bot)


def load():
    for i in range(0, QUANTITYPLOT):
        plotFiles.append(FSInputFile(f"plotFiles/photo{i}.jpg"))


if __name__ == "__main__":
    load()
    asyncio.run(main())
