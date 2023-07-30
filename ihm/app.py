import json
from service.Module_ihm import ihm
from flask import Flask, render_template, send_from_directory, request
app = Flask(__name__, static_folder='static')

objclient = ihm()


@app.route('/')
def index():
    return render_template('index.html')


@app.route('/stop')
def stop():
    stop = {
        "password": "ckai8MEoQ3cky6qHBqN7",
        "token":
            {"direction": 1},
        "value": 0
    }

    objclient.sendClient(stop)


@app.route('/rotateleft')
def rotateleft():
    rotateleft = {
        "password": "ckai8MEoQ3cky6qHBqN7",
        "token":
            {"direction": 1},
        "value": 1
    }

    objclient.sendClient(rotateleft)


@app.route('/rotateright')
def rotateright():
    rotateright = {
        "password": "ckai8MEoQ3cky6qHBqN7",
        "token":
            {"direction": 1},
        "value": 3
    }

    objclient.sendClient(rotateright)


@app.route('/slideleft')
def slideleft():
    slideleft = {
        "password": "ckai8MEoQ3cky6qHBqN7",
        "token":
            {"direction": 1},
        "value": 4
    }

    objclient.sendClient(slideleft)


@app.route('/slideright')
def slideright():
    slideright = {
        "password": "ckai8MEoQ3cky6qHBqN7",
        "token":
            {"direction": 1},
        "value": 5
    }

    objclient.sendClient(slideright)


@app.route('/forward')
def forward():
    forward = {
        "password": "ckai8MEoQ3cky6qHBqN7",
        "token":
            {"direction": 1},
        "value": 2
    }

    objclient.sendClient(forward)


@app.route('/backward')
def backward():
    backward = {
        "password": "ckai8MEoQ3cky6qHBqN7",
        "token":
            {"direction": 1},
        "value": 6
    }

    objclient.sendClient(backward)


@app.route('/posemine')
def posemine():
    posemine = {
        "password": "ckai8MEoQ3cky6qHBqN7",
        "token":
            {"mine": 3},
        "value": 1
    }
    objclient.sendClient(posemine)


@app.route('/nbmine')
def nbmine():
    nbmine = {
        "password": "ckai8MEoQ3cky6qHBqN7",
        "token":
            {"askNbMine": 4},
        "value": 1
    }

    objclient.sendClient(nbmine)


@app.route('/accroche')
def accroche():
    accroche = {
        "password": "ckai8MEoQ3cky6qHBqN7",
        "token":
            {"accroche": 2},
        "value": 1
    }

    objclient.sendClient(accroche)


@app.route('/claw1')
def claw1():
    claw1 = {
        "password": "ckai8MEoQ3cky6qHBqN7",
        "token":
            {"bras": 11},
        "value": 1
    }

    objclient.sendClient(claw1)


@app.route('/claw2')
def claw2():
    claw2 = {
        "password": "ckai8MEoQ3cky6qHBqN7",
        "token":
            {"bras": 11},
        "value": 2
    }

    objclient.sendClient(claw2)


@app.route('/motorA1')
def motorA1():
    motorA1 = {
        "password": "ckai8MEoQ3cky6qHBqN7",
        "token":
            {"bras": 11},
        "value": 3
    }

    objclient.sendClient(motorA1)


@app.route('/motorA2')
def motorA2():
    motorA2 = {
        "password": "ckai8MEoQ3cky6qHBqN7",
        "token":
            {"bras": 11},
        "value": 4
    }

    objclient.sendClient(motorA2)


@app.route('/motorB1')
def motorB1():
    motorB1 = {
        "password": "ckai8MEoQ3cky6qHBqN7",
        "token":
            {"bras": 11},
        "value": 5
    }

    objclient.sendClient(motorB1)


@app.route('/motorB2')
def motorB2():
    motorB2 = {
        "password": "ckai8MEoQ3cky6qHBqN7",
        "token":
            {"bras": 11},
        "value": 6
    }

    objclient.sendClient(motorB2)


@app.route('/motorC1')
def motorC1():
    motorC1 = {
        "password": "ckai8MEoQ3cky6qHBqN7",
        "token":
            {"bras": 11},
        "value": 7
    }

    objclient.sendClient(motorC1)


@app.route('/motorC2')
def motorC2():
    motorC2 = {
        "password": "ckai8MEoQ3cky6qHBqN7",
        "token":
            {"bras": 11},
        "value": 8
    }

    objclient.sendClient(motorC2)


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=80, debug=True)
