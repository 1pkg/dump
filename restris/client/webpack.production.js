const Fs = require('fs')
const Path = require('path')
const Webpack = require('webpack')
const UglifyPlugin = require('uglifyjs-webpack-plugin')
const HtmlPlugin = require('html-webpack-plugin')

var parameters = Fs.readFileSync('parameters.json')
module.exports = {
    entry: './source/application.js',

    output: {
        publicPath: '/',
        path: Path.join(__dirname, 'dump', 'build'),
        filename: 'bundle.js',
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
            NODE_ENV: 'production',
            DEBUG: false,
        }),
        new Webpack.DefinePlugin(JSON.parse(parameters)),
        new UglifyPlugin({
            parallel: true,
            sourceMap: false,
        }),
        new HtmlPlugin({
            template: 'templates/main.html',
            hash: true,
            minify: {
                html5: true,
                collapseInlineTagWhitespace: true,
                collapseWhitespace: true,
                keepClosingSlash: true,
                minifyCSS: true,
                minifyJS: true,
                minifyURLs: true,
                quoteCharacter: '"',
                removeComments: true,
                removeEmptyAttributes: true,
                removeEmptyElements: false,
                removeOptionalTags: true,
                removeRedundantAttributes: true,
                sortAttributes: true,
                sortClassName: true,
                useShortDoctype: true,
            },
        }),
    ],
}
