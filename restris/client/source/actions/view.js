import Axios from 'axios'

import * as Constants from '~/constants'

export default id => {
    return new Promise((resolve, reject) => {
        Axios.get(Constants.API_VIEW, { params: { id } })
            .then(response => {
                resolve({
                    type: Constants.ACTION_VIEW,
                    data: {
                        view: response.data.view,
                        preview: response.data.preview,
                    },
                })
            })
            .catch(exception => {
                reject(exception)
            })
    })
}
