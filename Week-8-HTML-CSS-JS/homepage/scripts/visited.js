// Adjust padding of tab-content based on footer height in px

function adjustContentPadding() {
    const footer = document.querySelector('.fixed-footer');
    const footerHeight = footer.offsetHeight;
    document.querySelector('.tab-content').style.paddingBottom = footerHeight + 'px';
}

window.addEventListener('load', adjustContentPadding);
window.addEventListener('resize', adjustContentPadding);

// Popover initialization
const popoverTriggerList = document.querySelectorAll('[data-bs-toggle="popover"]');
const popoverList = [...popoverTriggerList].map(el => new bootstrap.Popover(el));