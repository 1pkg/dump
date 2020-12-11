const Fs = require('fs')
const Path = require('path')
const Webpack = require('webpack')
const HtmlPlugin = require('html-webpack-plugin')

var parameters = Fs.readFileSync('parameters.json')
module.exports = {
    entry: './source/application.js',
    devtool: 'source-map',

    output: {
        publicPath: '/',
        path: Path.join(__dirname, 'dump', 'build'),
        filename: 'bundle.js',
    },

    devServer: {
        host: '0.0.0.0',
        port: 8080,
        inline: true,
        contentBase: './dump/build',
        historyApiFallback: true,
    },

    module: {
        rules: [
            {
                test: /\.jsx?$/,
                exclude: /(node_modules)/,
                use: {
                    loader: 'babel-loader',
                    options: {
                        presets: ['env', 'react'],
                        plugins: [
                            [
                                'babel-plugin-root-import',
                                {
                                    rootPathPrefix: '~',
                                    rootPathSuffix: 'source/',
                                },
                            ],
                            'transform-class-properties',
                            'transform-object-rest-spread',
                        ],
                    },
                },
            },
        ],
    },

    plugins: [
        new Webpack.EnvironmentPlugin({
            NODE_ENV: 'development',
            DEBUG: true,
        }),
        new Webpack.DefinePlugin(JSON.parse(parameters)),
        new HtmlPlugin({
            template: 'templates/main.html',
        }),
    ],
}
