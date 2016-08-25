'use strict';

(function() {
  // JavaScript Debounce Function
  // https://davidwalsh.name/javascript-debounce-function
  // -------------------------------------------------------------------------
  // Returns a function, that, as long as it continues to be invoked, will not
  // be triggered. The function will be called after it stops being called for
  // N milliseconds. If `immediate` is passed, trigger the function on the
  // leading edge, instead of the trailing.
  function debounce(func, wait, immediate) {
    var timeout;
    return function() {
      var context = this, args = arguments;
      var later = function() {
        timeout = null;
        if (!immediate) func.apply(context, args);
      };
      var callNow = immediate && !timeout;
      clearTimeout(timeout);
      timeout = setTimeout(later, wait);
      if (callNow) func.apply(context, args);
    };
  };

  // Adding an removing classes with vanilla JS
  // http://youmightnotneedjquery.com/#add_class
  // https://developer.mozilla.org/en-US/docs/Web/API/Element/classList

  function addClass(el, className) {
    if (el.classList) {
      // If these classes already exist in attribute of the element, then they are ignored.
      el.classList.add(className);
    }
    else {
      // safe-guard against adding classes twice
      if (el.className.indexOf(className) === -1) {
        el.className += ' ' + className;
      }
    }
  }

  function removeClass(el, className) {
    if (el.classList) {
      el.classList.remove(className);
    }
    else {
      var index = el.className.indexOf(className);
      if (index !== -1) {
        var cl = el.className.substring(0, index).trim();
        if (index + className.length != el.className.length) {
          if (cl !== '') cl += ' ';
          cl += el.className.substring(index+className.length).trim();
        }
        el.className = cl;
      }
    }
  }

  function setupCollapsingHeader() {
    // console.log('setupCollapsingHeader');

    var el_header = document.getElementById('page-header');
    var header_minimized = false;

    function setHeaderState() {
      if (window.scrollY > 30) {
        if (!header_minimized) {
          addClass(el_header, 'page-header-small');
          header_minimized = true;
        }
      } else {
        if (header_minimized) {
          removeClass(el_header, 'page-header-small');
          header_minimized = false;
        }
      }
    };

    var scrollHandler = debounce(setHeaderState, 100);

    // disabled debouncing for smoother transitions
    window.addEventListener('scroll', setHeaderState);
  };

  document.addEventListener('DOMContentLoaded', function(e) {
    setupCollapsingHeader();
  });
})();