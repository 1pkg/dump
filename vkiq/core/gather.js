const Token = require('./token.js')

String.prototype.padLeft = function(size) {
    return new Array(size - this.length + 1).join('0') + this
}

let Gather = function(raw) {
    Token.call(this, raw)
}
Gather.prototype = Object.create(Token)
Gather.prototype.constructor = Gather
Gather.prototype.weight = function() {
    let weigth = 0.0
    for (let i = 0, len = this.raw.length; i < len; ++i) {
        weigth += this.raw[i].weight()
    }
    let obj = {}
    let arr = Array.from(
        Math.round(weigth)
            .toString(2)
            .substr(0, 128)
            .padLeft(128),
    ).map(Number)
    arr.forEach((x, index) => {
        obj[String.fromCharCode(index)] = x
    })
    return obj
}
module.exports = Gather
