const add_button = document.getElementById('add_exercise');
const exercises = document.querySelector('.exercises');
const exercise = document.querySelector('.exercise');

add_button.addEventListener('click', e => {
  const new_exercise = exercise.cloneNode(true);

  const delete_button = document.createElement('button');
  delete_button.classList.add('delete_button')
  delete_button.textContent = '-';
  delete_button.type = 'button';

  new_exercise.appendChild(delete_button)
  exercises.append(new_exercise);

  delete_button.addEventListener('click', () => {
    new_exercise.remove();
  });
});
