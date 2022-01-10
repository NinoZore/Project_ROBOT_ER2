from flask import Flask, render_template, jsonify, request
import smbus2 as smbus
import time, threading

app = Flask(__name__, template_folder = "static/")
addrD = 0x27 # addr de l'arduino(i2c)
addrG = 0x25
code_recu = "en attente"
arduinobus = smbus.SMBus(1) # creation du bus i2c   
recu = 0
CODE_HTML = 0
Avancer = 0
Reculer = 0
TournerGauche = 0
TournerDroite = 0

@app.route("/")
def index():
    return render_template("index.html")
    
@app.route("/button",methods = ["POST"])#si on va sur /button on
def bouton():
    global code_recu
    global Avancer
    global Reculer
    global TournerGauche
    global TournerDroite
    print(request.get_json())
        
    bouton_appuyer = request.get_json()
    if bouton_appuyer == "AVANCER":
        if Avancer == 0:  
            #arduinobus.write_byte(addrD, 81)
            #arduinobus.write_byte(addrG, 81)
            code_recu = "CODE I2C GAUCHE = 81 et CODE I2C DROITE = 81"
            Avancer = 1
        else :
            #arduinobus.write_byte(addrD, 80)
            #arduinobus.write_byte(addrG, 80)
            code_recu = "CODE I2C GAUCHE = 80 et CODE I2C DROITE = 80"
            Avancer = 0
        print("avance")   

    if bouton_appuyer == "RECULER":
        if Reculer == 0: 
            #arduinobus.write_byte(addrD, 79)
            #arduinobus.write_byte(addrG, 79)
            code_recu = "CODE I2C GAUCHE = 79 et CODE I2C DROITE = 79"
            Reculer = 1
        else :
            #arduinobus.write_byte(addrD, 80)
            #arduinobus.write_byte(addrG, 80)
            code_recu = "CODE I2C GAUCHE = 80 et CODE I2C DROITE = 80"
            Reculer = 0
        print("recule")     

    if bouton_appuyer == "TOURNER GAUCHE":
        if TournerGauche == 0:
            #arduinobus.write_byte(addrD, 81)
            #arduinobus.write_byte(addrG, 79)
            code_recu = "CODE I2C GAUCHE = 79 et CODE I2C DROITE = 81"
            TournerGauche = 1
        else :
            #arduinobus.write_byte(addrD, 80)
            #arduinobus.write_byte(addrG, 80)
            code_recu = "CODE I2C GAUCHE = 80 et CODE I2C DROITE = 80"
            TournerGauche = 0
        print("tourne gauche")  
          
    if bouton_appuyer == "TOURNER DROITE":
        if TournerDroite == 0:
            #arduinobus.write_byte(addrD, 79)
            #arduinobus.write_byte(addrG, 81)
            code_recu = "CODE I2C GAUCHE = 81 et CODE I2C DROITE = 79"
            TournerDroite = 1
        else:
            #arduinobus.write_byte(addrD, 80)
            #arduinobus.write_byte(addrG, 80)
            code_recu = "CODE I2C GAUCHE = 80 et CODE I2C DROITE = 80"
            TournerDroite = 0
        print("tourne droite")
        
    return ("un truc")

@app.route("/code")#si on va sur /message on retourne le json { "message": "nouvelle valeur"}
def I2C_CODE():
    global CODE_HTML #variable python pour changer 
    return jsonify(CODE_JS = CODE_HTML)

def WEB():
    global CODE_HTML
    test = 0 
    while True:
        CODE_HTML = code_recu       
        #arduinobus.write_byte(addr, 101)
        #time.sleep(0.5)
        #battery = arduinobus.read_byte(addr)

threadWEB = threading.Thread(target=WEB)
threadWEB.start()
app.run(host='0.0.0.0')
