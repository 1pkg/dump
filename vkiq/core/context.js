const Token = require('./token.js')

let Context = function(raw) {
    Token.call(this, raw)
}
Context.prototype = Object.create(Token)
Context.prototype.constructor = Context
Context.prototype.weight = function() {
    let context = ''
    for (let i = 0, len = this.raw.length; i < len; ++i) {
        context += this.raw[i].weight()
    }
    return Number.parseFloat(context)
}
module.exports = Context
