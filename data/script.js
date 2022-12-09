/**
    Gestion de la vue
    @file script.js
    @author David Pigeon
    @version 1.0 2022-12-09  
*/
var boisChoisi;
var temperature = 0;
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
                        document.getElementById("listeBois").innerHTML += "<option value='" + idBois + "'>" + nomBois + "</option>";
                    }
                    
                    document.getElementById("listeBois").addEventListener("change", getCaracteristiqueBois);
                    window.addEventListener("load", getCaracteristiqueBois());
                }
            }
        };
    xhttp.open("GET", "getlisteNomBois", true);
    xhttp.send();
}
function getCaracteristiqueBois(){
    var idBois = document.getElementById("listeBois").value;
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function()
        {
            if(this.readyState == 4 && this.status == 200) {
                if(this.responseText.length > 0) {            
                    var description = JSON.parse(this.responseText);
                    console.log(description);
                    for(i = 0; i < description.results.length; i++){
                        boisChoisi = description.results[i];
                        document.getElementById("tempMin").innerHTML = description.results[i].tempMin;
                        document.getElementById("nomDuBois").innerHTML = description.results[i].nom;
                        document.getElementById("typeBois").innerHTML = description.results[i].type;
                        document.getElementById("origineBois").innerHTML = description.results[i].origine;
                        document.getElementById("dryingBois").innerHTML = description.results[i].drying;
                        document.getElementById("nomDuBois2").innerText = description.results[i].nom;
                        document.getElementById("dryingBois2").innerText = description.results[i].drying;
                        document.getElementById("tempMin2").innerText = description.results[i].tempMin;
                        document.getElementById("dryingBois2").value = description.results[i].drying
                        document.getElementById("tempMin2").value = description.results[i].tempMin;
                        
                    }
                    document.getElementById("four").addEventListener("click", four);
                }
            }
        };
    xhttp.open("GET", "bois?idBois="+idBois, true);
    xhttp.send();
}

setInterval(function getFromEsp_TemperatureSensor(){
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function(){
        if(this.readyState == 4 && this.status == 200){
            document.getElementById("temp").innerHTML = this.responseText;
            temperature = this.responseText;
        }
    };
    xhttp.open("GET", "getTemperatureSensor", true);
    xhttp.send();
    }, 3000);

function four(){
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "sendBoisInfo?drying="+boisChoisi.drying+"&tempMin="+boisChoisi.tempMin, true);
    xhttp.send();
    startCountdown();
}

function startCountdown(){
    var timeToWait = document.getElementById("dryingBois2").innerText;
    var i = -1;
    var temp = parseFloat(temperature);
    var timer = setInterval(function (){
        i++;
        document.getElementById("timer").innerText = i;
        if(temp < boisChoisi.tempMin){
            i--;
        }
        if(i == timeToWait){
            document.getElementById("timer").innerText = "0";
            clearInterval(timer);
        }
    }, 1000);
}

window.addEventListener("load", getFromEsp_StateLed());
function getFromEsp_StateLed(){
    setInterval(function(){
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function(){
            if(this.readyState == 4 && this.status == 200){
                if(this.responseText == "OFF"){
                    document.getElementById("cercleVert").style.backgroundColor = "green";
                    document.getElementById("cercleRouge").style.backgroundColor = "white";
                    document.getElementById("cercleOrange").style.backgroundColor = "white";
                    document.getElementById("four").removeAttribute("disabled", "true");
                }
                else if(this.responseText == "COLD"){
                    document.getElementById("cercleVert").style.backgroundColor = "white";
                    document.getElementById("cercleRouge").style.backgroundColor = "red";
                    document.getElementById("cercleOrange").style.backgroundColor = "white";
                    document.getElementById("four").setAttribute("disabled", "true");
                }
                else if(this.responseText == "HEAT"){
                    document.getElementById("cercleVert").style.backgroundColor = "white";
                    document.getElementById("cercleRouge").style.backgroundColor = "white";
                    document.getElementById("cercleOrange").style.backgroundColor = "orange";
                    document.getElementById("four").setAttribute("disabled", "true");
                }
                
            }
        };
        xhttp.open("GET", "getStateLed", true);
        xhttp.send();
    }, 1000);
    };




