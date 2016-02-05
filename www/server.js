var express = require('express');
var app = express();
var html = require('html');


var fs = require('fs')



app.use(express.static('_site'));


app.get('/', function(req, res){
	res.render('index.html')
})

app.listen(80);


