import React from 'react'
import Dialog from 'material-ui/Dialog'
import TextField from 'material-ui/TextField'
import FlatButton from 'material-ui/FlatButton'
import * as Colors from 'material-ui/styles/colors'

export default class extends React.Component {
    state = {
        error: false,
    }

    process = () => {
        let nickname = this.textField.input.value
        if (nickname.length >= 3 && nickname.length <= 7) {
            this.props.initialize(nickname)
        } else {
            this.setState(state => {
                return { error: true }
            })
        }
    }

    render() {
        return (
            <div>
                <Dialog
                    contentStyle={{ width: '50%' }}
                    actions={[
                        <FlatButton
                            onClick={this.process}
                            label="Process"
                            primary
                        />,
                    ]}
                    overlayStyle={{ backgroundColor: Colors.blueGrey50 }}
                    open={true}
                    modal
                >
                    <TextField
                        hintText="Tommy Wiseau"
                        floatingLabelText="Nickname"
                        floatingLabelFixed={true}
                        errorText={
                            this.state.error
                                ? 'Nicname should has at least 3 symbols and not exceed 7 symbols.'
                                : ''
                        }
                        ref={textField => {
                            this.textField = textField
                        }}
                    />
                </Dialog>
            </div>
        )
    }
}
