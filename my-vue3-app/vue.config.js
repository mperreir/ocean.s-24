module.exports ={
  pages: {
    user: {
      entry: 'src/pages/user/main.js',
      template: 'public/user.html',
      filename: 'user.html',
      title: 'User Page',
    },
    data: {
      entry: 'src/pages/data/main.js',
      template: 'public/data.html',
      filename: 'data.html',
      title: 'Data Page',
    },
  },
};
