var addon = require('./build/Release/addon.node');

console.log("Loaded addon");

var answer = new addon.Answer();

console.log("Created answer object");

var array = answer.reply("Botas", 12312, 123123, 1);

for(var i = 0; i < array.length; i++)
{
	var obj = array[i];
	console.log(obj.message);
}
