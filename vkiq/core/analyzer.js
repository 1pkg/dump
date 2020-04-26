const Brain = require('brain')

let Analyzer = function() {
    this.brain = new Brain.NeuralNetwork()
}
Analyzer.prototype.train = function(data) {
    this.brain.train(data, {
        log: true,
        logPeriod: 5,
        learningRate: 0.3,
        errorThresh: 0.00005,
        iterations: 30,
    })
}
Analyzer.prototype.analyze = function(set) {
    return this.brain.run(set)
}
module.exports = Analyzer
