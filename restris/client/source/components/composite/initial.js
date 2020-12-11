import React from 'react'

import Porter from '~/components/service/porter'

export default class extends React.Component {
    render() {
        return (
            <div style={{ width: '100%', height: '100%', display: 'flex' }}>
                <Porter initialize={this.props.initialize} />
            </div>
        )
    }
}
