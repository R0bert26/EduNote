function show_section(sectionId) {
    const sections = document.querySelectorAll('.section');
    sections.forEach(section => section.classList.remove('active'));

    document.getElementById(sectionId).classList.add('active');
}


function handle_submit(event, sectionId) {
    const form = event.target;
    form.reset();

    if (sectionId === 'add-user' || sectionId === 'delete-user') {
        const message = document.getElementById(`${sectionId}-msg`);
        message.classList.add('visible');

        setTimeout(() => {
            message.classList.remove('visible');
        }, 5000000);
    }
}
