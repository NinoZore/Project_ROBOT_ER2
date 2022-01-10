from flask import Flask, render_template, jsonify, request
import smbus2 as smbus
import time, threading

CODE = 0
addrD = 0x27 # addr de l'arduino(i2c)
addrG = 0x25
arduinobus = smbus.SMBus(1) # creation du bus i2c   
recu = 0

Avance = 0
Recule = 0
Tourne_Gauche = 0
Tourne_Droite = 0

app = Flask(__name__, template_folder = "static/")

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/button",methods = ["POST"])#si on va sur /button on
def bouton():
    global Avance
    global Recule
    global Tourne_Gauche
    global Tourne_Droite
    global bouton_appuyer
    print(request.get_json())
        
    bouton_appuyer = request.get_json()
    if bouton_appuyer == "AVANCER":
        #arduinobus.write_byte(addrD, 81)
        #arduinobus.write_byte(addrG, 81)
        print("avance")   

    if bouton_appuyer == "RECULER":
        #arduinobus.write_byte(addrD, 79)
        #arduinobus.write_byte(addrG, 79)
        print("recule")     

    if bouton_appuyer == "TOURNER_GAUCHE":
        #arduinobus.write_byte(addrD, 81)
        #arduinobus.write_byte(addrG, 79)
        print("tourne gauche")  
          
    if bouton_appuyer == "TOURNER DROITE":
        #arduinobus.write_byte(addrD, 79)
        #arduinobus.write_byte(addrG, 81)
        print("tourne droite")    

@app.route("/code")#si on va sur /message on retourne le json { "message": "nouvelle valeur"}
def I2C_CODE():
    global CODE #variable python pour changer 
    return jsonify(CODE_JS = CODE)

def WEB():

    while True:
        CODE = bouton_appuyer
        #arduinobus.write_byte(addr, 101)
        #time.sleep(0.5)
        #battery = arduinobus.read_byte(addr)
        time.sleep(1)

threadWEB = threading.Thread(target=WEB)
threadWEB.start()
app.run(host='0.0.0.0')
