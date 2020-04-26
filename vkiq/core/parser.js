const Vk = require('vk-io')

let Parser = function() {
    this.vk = new Vk({
        app: 'app',
        key: 'key',
    })
}
Parser.prototype.parse = function(domain) {
    return new Promise((resolve, reject) => {
        this.vk.auth.server().then(() => {
            this.vk.api.users
                .get({
                    user_ids: domain,
                    fields: 'id',
                })
                .then(data => {
                    let id = data[0].id
                    this.fetch(id, 0).then(
                        posts => resolve(posts),
                        message => reject(message),
                    )
                })
                .catch(data => reject(data))
        })
    })
}
Parser.prototype.fetch = function(id, offset) {
    return new Promise((resolve, reject) => {
        let buffer = []
        let callback = (id, offset) => {
            this.vk.api.wall
                .get({
                    owner_id: id,
                    count: 100,
                    offset: offset,
                    filter: 'all',
                })
                .then(data => {
                    data.items.forEach(item => {
                        let dpost =
                            item.copy_history && item.copy_history.length > 0
                                ? item.copy_history[0]
                                : item
                        if (dpost.text.length > 30 && dpost.date > 1420070400) {
                            let image = null
                            if (dpost.attachments) {
                                dpost.attachments.forEach(attachment => {
                                    if (
                                        !image &&
                                        attachment &&
                                        attachment.type === 'photo' &&
                                        attachment.photo
                                    ) {
                                        image = attachment.photo.photo_75
                                    }
                                })
                            }
                            buffer.push({
                                image: image
                                    ? image
                                    : 'https://screenshotlayer.com/images/assets/placeholder.png',
                                text: dpost.text,
                            })
                        }
                    })

                    if (buffer.length > 100 || data.items.length < 100) {
                        resolve(buffer)
                    } else {
                        callback(id, offset + 100)
                    }
                })
                .catch(data => reject(data))
        }
        callback(id, offset)
    })
}
module.exports = Parser
