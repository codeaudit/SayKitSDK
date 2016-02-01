var express = require('express');
var app = express();


var fs = require('fs')



app.configure('development', function(){
    app.use(express.static(__dirname + '/www/_site'))
})

app.use(express.bodyParser());

app.get('/', function(req, res){
	res.render('index.html')
})

app.listen(80);
