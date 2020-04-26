const Fs = require('fs')
const Path = require('path')
const Shuffle = require('shuffle-array')

let Trainer = function(analyzer, tokenizer) {
    this.analyzer = analyzer
    this.tokenizer = tokenizer
}
Trainer.prototype.train = function() {
    let data = []
    let files = Fs.readdirSync(Path.join(__dirname, '../train/'))
    files.forEach(file => {
        data = data.concat(
            JSON.parse(
                Fs.readFileSync(Path.join(__dirname, '../train/', file)),
            ),
        )
    })
    data = data.map(data => {
        return {
            input: this.tokenizer.divide(data.text).weight(),
            output: { index: data.index },
        }
    })
    data = Shuffle(data, { copy: true })
    this.analyzer.train(data)
}
module.exports = Trainer
