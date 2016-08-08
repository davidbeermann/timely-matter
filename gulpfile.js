const JEKYLL_SERVER_ADDRESS = 'http://127.0.0.1:4000/timely-matter/';

const browser_sync = require('browser-sync').create();
const gulp = require('gulp');


gulp.task('default', [], function () {
    browser_sync.init({
        proxy: JEKYLL_SERVER_ADDRESS
    });

    gulp.watch('./_site/css/**/*.css', function(event) {
      browser_sync.reload();
    });
});