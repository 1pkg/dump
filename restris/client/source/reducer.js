import Store from 'store'
import ExpireStorePlugin from 'store/plugins/expire'
import DefaultsStorePlugin from 'store/plugins/defaults'

import * as Constants from './constants'

Store.addPlugin(ExpireStorePlugin)
Store.addPlugin(DefaultsStorePlugin)
Store.setex = (key, value) => Store.set(key, value, Date.now() + 1800000)
Store.defaults({
    state: { id: null, nickname: '', rating: {}, score: 0, over: false },
})

export default (state = null, action) => {
    let buffer = state ? Object.assign({}, state) : {}
    switch (action.type) {
        case Constants.ACTION_INITIALIZE:
        case Constants.ACTION_INTERACT:
        case Constants.ACTION_UPDATE:
        case Constants.ACTION_VIEW:
            buffer = Object.assign(buffer, action.data)
            Store.setex('state', buffer)
            return buffer

        default:
            buffer = Object.assign(buffer, Store.get('state'))
            return buffer
    }
}
