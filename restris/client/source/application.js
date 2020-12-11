import * as Redux from 'redux'
import * as ReactRedux from 'react-redux'
import ReduxThunk from 'redux-thunk'
import React from 'react'
import ReactDOM from 'react-dom'
import MuiThemeProvider from 'material-ui/styles/MuiThemeProvider'
import GetMuiTheme from 'material-ui/styles/getMuiTheme'
import DarkBaseTheme from 'material-ui/styles/baseThemes/darkBaseTheme'

import Reducer from './reducer'
import Main from './components/main'

let compose =
    process.env.NODE_ENV !== 'production' &&
    window.__REDUX_DEVTOOLS_EXTENSION_COMPOSE__
        ? window.__REDUX_DEVTOOLS_EXTENSION_COMPOSE__
        : Redux.compose

let store = Redux.createStore(
    Reducer,
    compose(Redux.applyMiddleware(ReduxThunk)),
)

ReactDOM.render(
    <ReactRedux.Provider store={store}>
        <MuiThemeProvider muiTheme={GetMuiTheme(DarkBaseTheme)}>
            <Main />
        </MuiThemeProvider>
    </ReactRedux.Provider>,
    document.getElementById('main'),
)
