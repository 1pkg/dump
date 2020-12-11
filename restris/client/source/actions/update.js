import Axios from 'axios'

import * as Constants from '~/constants'

export default id => {
    return new Promise((resolve, reject) => {
        Axios.get(Constants.API_UPDATE, { params: { id } })
            .then(response => {
                if (response.data.over) {
                    resolve({
                        type: Constants.ACTION_UPDATE,
                        data: {
                            rating: response.data.rating,
                            score: response.data.score,
                            over: response.data.over,
                        },
                    })
                } else {
                    resolve({
                        type: Constants.ACTION_UPDATE,
                        data: {
                            score: response.data.score,
                            over: response.data.over,
                        },
                    })
                }
            })
            .catch(exception => {
                reject(exception)
            })
    })
}
