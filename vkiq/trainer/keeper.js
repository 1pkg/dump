const fs = require('fs')
const path = require('path')

let Keeper = function() {
    this.root = path.join(__dirname, '../train')
}
Keeper.prototype.keep = function(domain, data) {
    let file = path.join(this.root, domain + '.json')
    let json = JSON.stringify(data, null, 2)
    fs.writeFile(file, json)
}
module.exports = Keeper
