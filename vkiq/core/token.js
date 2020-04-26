let Token = function(raw) {
    this.raw = raw
}
Token.prototype.weight = function() {
    return -1
}
module.exports = Token
