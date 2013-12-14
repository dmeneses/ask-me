var addon = require('./build/Release/addon.node');

console.log("Loaded addon");

var answer = new addon.Answer();

console.log("Created answer object");

var array = answer.reply("Trabajando", -17.365978, -66.175486, 1);

for(var i = 0; i < array.length; i++)
{
	var obj = array[i];
	console.log(obj.message);
}
