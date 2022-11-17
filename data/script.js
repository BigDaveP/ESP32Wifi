
window.addEventListener("load", getNomBois());
function getNomBois(){
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function()
        {
            if(this.readyState == 4 && this.status == 200) {
                if(this.responseText.length > 0) {            
                    var description = JSON.parse(this.responseText);
                    
                    for(var i = 0; i < description.results.length; i++) {
                        var nomBois = description.results[i].nom;
                        var idBois = description.results[i].id;
                        document.getElementById("nomBois").innerHTML += "<option value='" + idBois + "'>" + nomBois + "</option>";
                        document.getElementById("nomBois").style.color = "red";
                    }
                    
                    document.getElementById("nomBois").addEventListener("change", getCaracteristiqueBois);
                }
            }
        };
    xhttp.open("GET", "oui", true);
    xhttp.send();
}


function getCaracteristiqueBois(){
    var idBois = document.getElementById("nomBois").value;
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function()
        {
            if(this.readyState == 4 && this.status == 200) {
                if(this.responseText.length > 0) {            
                    var description = JSON.parse(this.responseText);
                    console.log(description);
                    document.getElementById("caracteristiqueBois").innerHTML = "Caractéristique du bois : " + description.results[0].caracteristique;
                    document.getElementById("caracteristiqueBois").style.color = "red";
                }
            }
        };
    xhttp.open("GET", "oui", true);
    xhttp.send();
}

//permet d'envoyer les données au serveur
function sendBois(){
    var idBois = document.getElementById("nomBois").value;
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function()
        {
            if(this.readyState == 4 && this.status == 200) {
                if(this.responseText.length > 0) {            
                    var description = JSON.parse(this.responseText);
                    console.log(description);
                    document.getElementById("caracteristiqueBois").innerHTML = "Caractéristique du bois : " + description.results[0].caracteristique;
                    document.getElementById("caracteristiqueBois").style.color = "red";
                }
            }
        };
    xhttp.open("GET", "oui", true);
    xhttp.send();
}




