const Path = require('path')
const Tokenizer = require('./core/tokenizer.js')
const Analyzer = require('./core/analyzer.js')
const Trainer = require('./core/trainer.js')
const Parser = require('./core/parser.js')
const Express = require('express')
const BodyParser = require('body-parser')
const BasicAuthConnect = require('basic-auth-connect')

let parser = new Parser()
let tokenizer = new Tokenizer()
let analyzer = new Analyzer()
let trainer = new Trainer(analyzer, tokenizer)
setTimeout(() => {
    console.log('train start')
    trainer.train()
    console.log('train done')
}, 10000)

let express = Express()
express.set('view engine', 'pug')
express.set('views', Path.join(__dirname, 'temlates'))
express.use(Express.static('static'))
express.use(BodyParser.json())
express.use(BodyParser.urlencoded({ extended: true }))
express.use(BasicAuthConnect('myiq', 'over9000'))

express.get('/', (request, response) => {
    response.render('index')
})
express.get('/task', (request, response) => {
    let results = []
    ;[
        { domain: 'https://vk.com/dm', description: 'медведев' },
        { domain: 'https://vk.com/o.liashko', description: 'ляшко' },
        { domain: 'https://vk.com/id26867380', description: 'шарий' },
        { domain: 'https://vk.com/volodymyr.parasiuk', description: 'парасюк' },
        { domain: 'https://vk.com/id38940203', description: 'жириновский' },
        { domain: 'https://vk.com/id41362423', description: 'зюганов' },
        { domain: 'https://vk.com/id129244038', description: 'навальный ^^' },
        { domain: 'https://vk.com/id270275789', description: 'валуев' },
        { domain: 'https://vk.com/gennadiy.balashov', description: 'балашов' },
        { domain: 'https://vk.com/oleg.tsarov', description: 'царёв' },
        { domain: 'https://vk.com/id103763193', description: 'яровая' },
        { domain: 'https://vk.com/id3011920', description: 'милонов' },
        { domain: 'https://vk.com/id12086666', description: 'миронов' },
        { domain: 'https://vk.com/id279938622', description: 'кадыров' },
    ].forEach(item => {
        parser.parse(item.domain.replace('https://vk.com/', '')).then(
            data => {
                let result = {
                    domain: item.domain,
                    description: item.description,
                    index: 0.0,
                    posts: [],
                }
                if (data.length > 5) {
                    data.forEach(post => {
                        let analyzed = analyzer.analyze(
                            tokenizer.divide(post.text).weight(),
                        )
                        result.index += analyzed.index
                        result.posts.push({
                            preview: post.text.substr(0, 50) + '...',
                            image: post.image,
                            index: Math.round(analyzed.index * 100),
                        })
                    })
                    result.index *= 100
                    result.index = Math.round(result.index / data.length)
                    results.push(result)
                } else {
                    return
                }
                if (results.length == 15) {
                    results.sort((l, r) => {
                        return r.index - l.index
                    })
                    response.render('task', { results: results })
                }
            },
            data => {
                return
            },
        )
    })
})
express.post('/analyze', (request, response) => {
    let domain = request.body.domain
    if (domain.indexOf('https://vk.com/') === -1) {
        response.setHeader('Content-Type', 'application/json')
        response.send(JSON.stringify({ message: 'введен не корректный url' }))
        return
    }
    parser.parse(domain.replace('https://vk.com/', '')).then(
        data => {
            let result = {
                domain: domain,
                index: 0.0,
                posts: [],
            }
            if (data.length > 5) {
                data.forEach(post => {
                    let analyzed = analyzer.analyze(
                        tokenizer.divide(post.text).weight(),
                    )
                    result.index += analyzed.index
                    result.posts.push({
                        preview: post.text.substr(0, 50) + '...',
                        image: post.image,
                        index: Math.round(analyzed.index * 100),
                    })
                })
                result.index *= 100
                result.index = Math.round(result.index / data.length)
            } else {
                response.setHeader('Content-Type', 'application/json')
                response.send(
                    JSON.stringify({
                        message: 'для анализа слишком мало данных',
                    }),
                )
                return
            }
            response.render('result', result)
        },
        data => {
            response.setHeader('Content-Type', 'application/json')
            response.send(
                JSON.stringify({ message: 'введен не корректный profile' }),
            )
            return
        },
    )
})
express.listen(process.env.PORT || 3000)
