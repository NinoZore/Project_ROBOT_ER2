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


@app.route("/")
def index():
    return render_template("index.html")
    
@app.route("/button",methods = ["POST"])#si on va sur /button on
def bouton():
    global code_recu
    print(request.get_json())
        
    bouton_appuyer = request.get_json()
    if bouton_appuyer == "AVANCER":
        #arduinobus.write_byte(addrD, 81)
        #arduinobus.write_byte(addrG, 81)
        code_recu = "avance"
        print("avance")   

    if bouton_appuyer == "RECULER":
        #arduinobus.write_byte(addrD, 79)
        #arduinobus.write_byte(addrG, 79)
        code_recu = "recule"
        print("recule")     

    if bouton_appuyer == "TOURNER GAUCHE":
        #arduinobus.write_byte(addrD, 81)
        #arduinobus.write_byte(addrG, 79)
        code_recu = "tourne gauche"
        print("tourne gauche")  
          
    if bouton_appuyer == "TOURNER DROITE":
        #arduinobus.write_byte(addrD, 79)
        #arduinobus.write_byte(addrG, 81)
        code_recu = "tourne droite"
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
        time.sleep(1)

threadWEB = threading.Thread(target=WEB)
threadWEB.start()
app.run(host='0.0.0.0')
