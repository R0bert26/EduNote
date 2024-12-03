function show_section(sectionId) {
    const sections = document.querySelectorAll('.section');
    sections.forEach(section => section.classList.remove('active'));

    document.getElementById(sectionId).classList.add('active');
}

function handle_submit(event, sectionId) {
    const form = event.target;
    
    if (sectionId === 'add-user') {
        alert('User added successfully');
    }
    else if (sectionId === 'delete-user') {
        alert('User deleted successfully');
    }

}
