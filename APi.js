//Test ftp
const express = require('express');
const mysql = require('mysql');
const cors = require ('cors');
const jwt = require('jsonwebtoken');
var XMLHttpRequest = require("xmlhttprequest").XMLHttpRequest;
var bodyParser = require("body-parser");
const app = express();
const port = process.env.PORT || 8080
const dotenv = require('dotenv');

dotenv.config();

process.env.TOKEN_SECRET;

var username = 'debian';
function generateAccessToken(username) {
  return jwt.sign(username, process.env.TOKEN_SECRET, { expiresIn: '1800s' });
}

function authenticateToken(req, res, next) {
  const authHeader = req.headers['authorization']
  const token = authHeader && authHeader.split(' ')[1]
  console.log(req.ip)
  var sql = 'INSERT INTO logs (ip, token, status) VALUES (?)';
  if(token == process.env.TOKEN_SECRET){
        var values = ["'"+req.ip+"'", "'"+token+"'", "Succès !"];
  }
  else{
        var values = ["'"+req.ip+"'", "'"+token+"'", "Connection bloquée !"];
  }

  connection.query(sql, [values]);
                if(token == process.env.TOKEN_SECRET){
                        next()

                }
                else{
                        return res.status(401).send("Échec de la connection");
                }
}

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json())
app.listen(port, () => console.log('Listen on port ' + port))

//Mysql
var connection = mysql.createConnection({
        host : '',
        user : 'debiansql',
        password : '!24Serpi43',
        database : 'SAC'
});

connection.connect();

app.use(cors());

//Permet de récupérer les informations de tous les bois
app.get('/bois', authenticateToken, function(req, res, next){
        connection.query('Select * from bois', function(error, results, fields){
        if (error) throw error;
        res.send(JSON.stringify({results}));
    });
});

//Permet de récupérer les informations d'un bois avec son id passé en paramètre
app.get('/bois/:id', authenticateToken,function(req, res, next){
    connection.query('Select * from bois where id = ?', [req.params.id], function(error, results, fields){
        if(error) throw error;
        res.send(JSON.stringify({results}));
    })
});
