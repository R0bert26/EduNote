const logoutBtn = document.querySelector('.logout-btn');
const AddUserBtn = document.querySelector('#add-user-btn');
const DeleteUserBtn = document.querySelector('#delete-user-btn');
const addUserForm = document.querySelector('#add-user-form');
const deleteUserForm = document.querySelector('#delete-user-form');


async function process_data(inputData) {
    const params = JSON.stringify(inputData);

    try {
        const response = await fetch('/admin', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: params
        });

        const data = await response.json();
        return data

    } catch (error) {
        alert(`${error.message}`);
        throw new Error(`${error.message}`);
    }
}


function show_section(sectionId) {
    const sections = document.querySelectorAll('.section');
    sections.forEach(section => section.classList.remove('active'));

    document.getElementById(sectionId).classList.add('active');
}


AddUserBtn.addEventListener('click', async () => {
    firstName = document.querySelector('#first-name').value.trim();
    lastName = document.querySelector('#last-name').value.trim();
    email = document.querySelector('#add-email').value.trim();
    password = document.querySelector('#password').value.trim();
    role = document.querySelector('input[name="role"]:checked').value;

    const inputData = {
        action: 'add_user',
        first_name: firstName,
        last_name: lastName,
        email: email,
        password: password,
        role: role
    };

    const data = await process_data(inputData);

    if (data.status === 'success') {
        alert(data.message);
    }
    else {
        alert(`${data.message}`);
    }

    addUserForm.reset();
})


DeleteUserBtn.addEventListener('click', async () => {
    email = document.querySelector('#delete-email').value.trim();

    const inputData = {
        action: 'delete_user',
        email: email
    };

    const data = await process_data(inputData);

    if (data.status === 'success') {
        alert(data.message);
    }
    else {
        alert(`${data.message}`);
    }

    deleteUserForm.reset();
})


logoutBtn.addEventListener('click', async () => {
    const inputData = {
        action: 'logout'
    };

    const data = await process_data(inputData);

    if (data.status === 'success') {
        window.location.href = '/';
    }
    else {
        alert(`${data.message}`);
    }
})
