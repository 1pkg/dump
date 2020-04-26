const Token = require('./token.js')
const TABLE = {
    о: 1 / (10.97 / 100.0),
    е: 1 / (8.45 / 100.0),
    а: 1 / (8.01 / 100.0),
    и: 1 / (7.35 / 100.0),
    н: 1 / (6.7 / 100.0),
    т: 1 / (6.26 / 100.0),
    с: 1 / (5.47 / 100.0),
    р: 1 / (4.73 / 100.0),
    в: 1 / (4.54 / 100.0),
    л: 1 / (4.4 / 100.0),
    к: 1 / (3.49 / 100.0),
    м: 1 / (3.21 / 100.0),
    д: 1 / (2.98 / 100.0),
    п: 1 / (2.81 / 100.0),
    у: 1 / (2.62 / 100.0),
    я: 1 / (2.01 / 100.0),
    ы: 1 / (1.9 / 100.0),
    ь: 1 / (1.74 / 100.0),
    г: 1 / (1.7 / 100.0),
    з: 1 / (1.65 / 100.0),
    б: 1 / (1.59 / 100.0),
    ч: 1 / (1.44 / 100.0),
    й: 1 / (1.21 / 100.0),
    х: 1 / (0.97 / 100.0),
    ж: 1 / (0.94 / 100.0),
    ш: 1 / (0.73 / 100.0),
    ю: 1 / (0.64 / 100.0),
    ц: 1 / (0.48 / 100.0),
    щ: 1 / (0.36 / 100.0),
    э: 1 / (0.32 / 100.0),
    ф: 1 / (0.26 / 100.0),
    ъ: 1 / (0.04 / 100.0),
    ё: 1 / (0.04 / 100.0),
}

let Lema = function(raw) {
    Token.call(this, raw)
}
Lema.prototype = Object.create(Token)
Lema.prototype.constructor = Lema
Lema.prototype.weight = function() {
    let weight = 0
    for (let i = 0, len = this.raw.length; i < len; ++i) {
        let char = this.raw[i].toLowerCase()
        if (char in TABLE) {
            weight += TABLE[char]
        } else {
            weight += 0.0
        }
    }
    return Math.ceil(weight)
}
module.exports = Lema
