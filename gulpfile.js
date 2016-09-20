const JEKYLL_SERVER_ADDRESS = 'http://127.0.0.1:4000/timely-matter/';

const browser_sync = require('browser-sync').create();
const gulp = require('gulp');
const imagemin = require('gulp-imagemin');
const pngquant = require('imagemin-pngquant');
const rename = require('gulp-rename');
const uglify = require('gulp-uglify');


gulp.task('scripts', function () {
    gulp.src('./_source/*.js')
        .pipe(rename({suffix: '.min'}))
        .pipe(uglify())
        .pipe(gulp.dest('./js'));
});


gulp.task('images', function () {
    console.log('optimizing images');
    gulp.src('./_images/**/*')
        .pipe(imagemin({
            interlaced: true,
            optimizationLevel: 3,
            progressive: true,
            use: [pngquant()]
        }))
        .pipe(gulp.dest('./static/images'));
});


gulp.task('default', ['scripts','images'], function () {
    browser_sync.init({
        proxy: JEKYLL_SERVER_ADDRESS
    });

    gulp.watch('./_site/css/**/*.css', function(event) {
      browser_sync.reload();
    });

    gulp.watch('./_source/*.js', ['scripts'], function(event) {
      browser_sync.reload();
    });

    gulp.watch('./_images/**/*', ['images']);
});