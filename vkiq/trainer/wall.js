const Vk = require('vk-io')

let Wall = function(keeper) {
    this.vk = new Vk({
        app: '6010705',
        key: 'u01vlobc43gWGKfpHoMp',
    })
    this.keeper = keeper
}
Wall.prototype.parse = function(data) {
    this.vk.auth.server().then(() => {
        for (let i = 0, len = data.length; i < len; ++i) {
            this.fetch(data[i].domain, 0, 1000).then(buffer => {
                console.log('done: ' + data[i].domain)
                this.keeper.keep(
                    data[i].domain,
                    buffer.map(text => {
                        return { text: text, index: data[i].index }
                    }),
                )
            })
        }
    })
}
Wall.prototype.fetch = function(domain, offset, max) {
    return new Promise(resolve => {
        let buffer = []
        let func = (domain, offset, max) => {
            this.vk.api.wall
                .get({
                    domain: domain,
                    count: 100,
                    offset: offset,
                })
                .then(data => {
                    data.items.forEach(post => {
                        if (post.text.length > 30 && post.date > 1420070400) {
                            buffer.push(post.text)
                        }
                    })

                    if (
                        data.items.length < 100 ||
                        data.items[0].date < 1420070400 ||
                        buffer.length >= max
                    ) {
                        resolve(buffer)
                    } else {
                        func(domain, offset + 100, max)
                    }
                })
                .catch(error => {})
        }
        console.log('start: ' + domain)
        func(domain, offset, max)
    })
}
module.exports = Wall
