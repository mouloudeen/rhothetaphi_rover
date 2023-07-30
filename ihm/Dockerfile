FROM python:3.10.2-buster

RUN mkdir /code
WORKDIR /code
ADD . /code/

EXPOSE 80
RUN pip install --upgrade pip
RUN pip install -r requirements.txt


CMD [ "python", "./app.py" ]