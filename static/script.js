function CODEI2C(){
    
    fetch("/code")//on fait une requete a /message
    .then( data => {console.log(data);return data.json()})//on prend ce que ca nous renvoie et on retourne le json
    .then( j =>{//avec le json on va modifier la valeur pour la changer
        console.log(j);
        var valeur = document.getElementById("CODE_I2C")//variable html type : id

        valeur.innerText = j["CODE_JS"]//varriable python
    })
}

//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
function bouton_parametre(variable){
    fetch("/button", {method:'POST',headers:{'Accept': 'application/json', 'Content-Type': 'application/json'}, body:JSON.stringify(variable)} )    
}
//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo

setInterval(CODEI2C, 1000)
