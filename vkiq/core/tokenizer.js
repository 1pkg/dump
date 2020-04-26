const Lema = require('./lema.js')
const Context = require('./context.js')
const Gather = require('./gather.js')

let Tokenizer = function() {}
Tokenizer.prototype.divide = function(text) {
    let rawDotContexts = text.split('.')
    let rawNLContexts = text.split('\n')
    let rawContexts =
        rawDotContexts.length > rawNLContexts.length
            ? rawDotContexts
            : rawNLContexts
    let contexts = []
    for (let i = 0, leni = rawContexts.length; i < leni; ++i) {
        let rawLems = rawContexts[i].split(' ')
        let lems = []
        for (let j = 0, lenj = rawLems.length; j < lenj; ++j) {
            lems.push(new Lema(rawLems[j]))
        }
        contexts.push(new Context(lems))
    }
    return new Gather(contexts)
}
module.exports = Tokenizer
