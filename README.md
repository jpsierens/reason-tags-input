# app

Run this project:

```
npm install
npm start
# in another tab
npm run webpack
```

After you see the webpack compilation succeed (the `npm run webpack` step), open up the nested html files in `src/*` (**no server needed!**). Then modify whichever file in `src` and refresh the page to see the changes.

**For more elaborate ReasonReact examples**, please see https://github.com/reasonml-community/reason-react-example

## flow
By doing npm start. You are running the Reason compiler and watching for changes to Reason files (.re). When you make a change to one, it compiles it to JavaScript (.bs.js) through BuckleScript. When that happens, webpack picks up and does it's thing and throws the bundle to build/index.js. So it's a 2 step process:

BuckleScript -> Webpack -> output
