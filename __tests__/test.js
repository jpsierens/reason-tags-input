import React from 'react';
import { shallow, mount, configure } from 'enzyme';
import Adapter from 'enzyme-adapter-react-15';

import TagsInput from '../build';

configure({ adapter: new Adapter() });


describe('<TagsInput />', () => {
	it('should render', () => {
		expect(shallow(<TagsInput />).find('.react-tags-input').length).toBe(1);
	});

	it('should create a tag when the user enters text', () => {
		const onInput = () => false;
		const onRemove = () => false;
		const tagsInput = mount(<TagsInput onInput={onInput} onRemove={onRemove} />);
		console.log(tagsInput.state())
		// tagsInput.setState({  })
	});

	it('should render clear cta', () => {
		const tagsInput = shallow(<TagsInput onClear={() => 0} />);
		expect(tagsInput.find('.clear-all').length).toBe(1);
	});

	it('should render clear cta\'s default text', () => {
		const tagsInput = shallow(<TagsInput onClear={() => 0} />);
		expect(tagsInput.find('.clear-all').text()).toBe('Clear all');
	});

	it('should render clear cta\'s custom text', () => {
		const tagsInput = shallow(<TagsInput clearAllText="custom" onClear={() => 0} />);
		expect(tagsInput.find('.clear-all').text()).toBe('custom');
	});
});
