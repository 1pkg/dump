import Axios from 'axios'

import * as Constants from '~/constants'

export default (id, action, direction) => {
    return new Promise((resolve, reject) => {
        Axios.get(Constants.API_INTERACT, {
            params: { id, action, direction },
        })
            .then(response => {
                resolve({
                    type: Constants.ACTION_INTERACT,
                    data: {},
                })
            })
            .catch(exception => {
                reject(exception)
            })
    })
}
