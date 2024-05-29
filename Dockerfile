FROM python:3.10.4-alpine

RUN apk update && apk upgrade


LABEL authors="GuesWho_A"


RUN apk add --update --no-cache python3 && ln -sf python3 /usr/bin/python
RUN python3 -m ensurepip
RUN pip3 install --no-cache --upgrade pip setuptools

RUN pip install aiogram

COPY /plotFiles /plotFiles
COPY main.py main.py
COPY config.py config.py

CMD ["python", "main.py"]

