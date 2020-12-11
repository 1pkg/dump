import React from 'react'
import * as Colors from 'material-ui/styles/colors'

export default class extends React.Component {
    render() {
        return (
            <div
                style={{
                    flex: 1,
                    display: 'flex',
                    color: Colors.grey400,
                    backgroundColor: this.props.over
                        ? Colors.grey800
                        : Colors.blueGrey50,
                }}
                dangerouslySetInnerHTML={{ __html: this.props.view }}
            />
        )
    }
}
